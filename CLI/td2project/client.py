from time import sleep
from bluetooth import *

class HorarioBase:
     def __init__(self, horas, minutos, segundos):
         self.horas = str(horas).zfill(2)
         self.minutos = str(minutos).zfill(2)
         self.segundos = str(segundos).zfill(2)


class HC05:
     
     CMD_CLAVE = 'C'
     CMD_RFID = 'R'
     CMD_MEMORY = 'M'
     CMD_HORA = 'H'

     EVENTS = [
          'EVENT_ALARM_ON',
          'EVENT_ALARM_OFF',
          'EVENT_POWER_ON',
          'EVENT_POWER_OFF',
          'EVENT_ALARM_BEEP_SALA1',
          'EVENT_ALARM_BEEP_SALA2',
     ]


     def __init__(self, mac):
          print('Searching ALARM SYSTEM...')
          try:
               self.bt = BluetoothSocket( RFCOMM )
               port = 1
               self.password = '1234'
               self.bt.connect((mac, port))
          except btcommon.BluetoothError:
               print('Error! Device busy, try again in a few seconds.')
          except KeyboardInterrupt:
               self.bt.close()
          print('Device was found!')


     def set_pass(self, password):
          self.password = password

     def send_command(self, cmd, payload = None):
          if cmd is self.CMD_CLAVE: self.password = payload
          if cmd is self.CMD_RFID: payload = 'R'
          if cmd is self.CMD_MEMORY: payload = 'M'
          try:
               trama = '$'+ self.password + cmd + payload + chr(0xD) + chr(0xA)
               self.bt.send(trama)
          except:
               raise RuntimeError('Error on SEND!')

     def recv_data(self, size = 512):
          self.bt.settimeout(10)
          return self.bt.recv(size)

     def close(self):
          self.bt.close()

     def process_raw_data(self, raw_data):
          raw_frames = raw_data.split(b'$')
          not_empty_frames = [x for x in raw_frames if x]
          almost_final_frames = [frame[:-2] for frame in not_empty_frames]
          final_frames = [frame for frame in almost_final_frames if len(frame)==4]

          if not final_frames: raise RuntimeError('Error en el envío de datos.')
          
          print('======= EEPROM CONTENT ==========')
          for frame in final_frames:
               print(f'{self.EVENTS[frame[0]]} @ {frame[1]}:{frame[2]}:{frame[3]}')
          print('================================')


def init():
     hc05_addr = "00:21:07:34:DA:1B"
     return HC05(hc05_addr)


def get_mem():
     device = init()
     
     running = True
     print('Reading EEPROM..')
     while(running):
          try:
               sleep(1)
               device.send_command(device.CMD_MEMORY)
               raw_data = device.recv_data()
               running = False
          except btcommon.BluetoothError:
               print('Timed out. Retrying..')
               running = True
          except KeyboardInterrupt:
               device.close()

     device.process_raw_data(raw_data)
     device.close()
     

def set_pass():
     import argparse
     parser = argparse.ArgumentParser()
     parser.add_argument('new_pass', help='New password')
     parser.add_argument('--old_pass', required=False, default='1234', help='Old password')
     args = parser.parse_args()

     device = init()
     if args.old_pass: device.set_pass(args.old_pass)
     device.send_command(device.CMD_CLAVE, payload=str(args.new_pass))

     print('Command was sent')
     device.close()

def set_time():
     import argparse
     parser = argparse.ArgumentParser()
     parser.add_argument('--hs', required=True, default=1, help='Horas')
     parser.add_argument('--min', required=True, default=2, help='Minutos')
     parser.add_argument('--seg', required=True, default=3, help='Segundos')

     args = parser.parse_args()

     time = HorarioBase(args.hs, args.min, args.seg)
     device = init()
     payload = str(time.horas).zfill(2) + str(time.minutos).zfill(2) + str(time.segundos).zfill(2)
     device.send_command(device.CMD_HORA, payload)

     print('Command was sent')
     device.close()

def add_rfid():
     device = init()
     device.send_command(device.CMD_RFID)
     
     print('Command was sent')
     device.close()

if __name__ == '__main__':
     get_mem()
     # set_pass()


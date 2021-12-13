from time import sleep
from bluetooth import *

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
          self.bt = BluetoothSocket( RFCOMM )
          port = 1
          self.password = '1234'
          self.bt.connect((mac, port))

     def set_pass(self, password):
          self.password = password

     def send_command(self, cmd, payload = None):
          if cmd is self.CMD_CLAVE: self.password = payload
          if cmd is self.CMD_RFID: payload = 'R'
          if cmd is self.CMD_MEMORY: payload = 'M'
          try:
               self.bt.send('$'+ self.password + cmd + payload + chr(0xD) + chr(0xA))
          except:
               raise RuntimeError('Error on SEND!')

     def recv_data(self):
          self.bt.settimeout(5)
          return self.bt.recv(512)

     def close(self):
          self.bt.close()

     def process_raw_data(self, raw_data):
          raw_frames = raw_data.split(b'$')
          not_empty_frames = [x for x in raw_frames if x]
          almost_final_frames = [frame[:-2] for frame in not_empty_frames]
          final_frames = [frame for frame in almost_final_frames if len(frame)==4]

          if not final_frames: raise RuntimeError('Error en el enviío de datos.')
          
          print('======= EEPROM CONTENT ==========')
          for frame in final_frames:
               print(f'{self.EVENTS[frame[0]]} @ {frame[1]}:{frame[2]}:{frame[3]}')
          print('================================')


def init():
     hc05_addr = "00:21:07:34:DA:1B"
     return HC05(hc05_addr)


def read_mem():
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

     device.close()


if __name__ == '__main__':
     read_mem()
     # set_pass()


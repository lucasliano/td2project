import bluetooth as bt

devices = bt.discover_devices(lookup_names=True)
print(f'Dispositivos disponibles: {devices}')

handler = bt.BluetoothSocket('HCI')

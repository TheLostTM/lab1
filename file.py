import serial
import time
import serial.tools.list_ports

speeds = ['1200', '2400', '4800', '9600', '19200', '38400', '57600', '115200']
ports = [p.device for p in serial.tools.list_ports.comports()]
port_name = ports[0]
port_speed = int(speeds[-1])
port_timeout = 10

ard = serial.Serial(port_name, port_speed, timeout=port_timeout)
time.sleep(1)
ard.flushInput()

try:
    msg_bin = ard.read(ard.inWaiting())
    msg_bin += ard.read(ard.inWaiting())
    msg_bin += ard.read(ard.inWaiting())
    msg_bin += ard.read(ard.inWaiting())

    msg_str_ = msg_bin.decode()
    print(len(msg_bin))

except Exception as e:
    print('Error!')

ard.close()
time.sleep(1)
print(msg_str_)



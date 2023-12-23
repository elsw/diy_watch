from datetime import datetime
import serial

port = "COM11"

serial = serial.Serial(port)

serial.write(b's')
ret = serial.readline()
print(ret)
c = datetime.now()
buffer = bytearray(4)
current_time = c.strftime('%H%M%S')
buffer[0] = ord('t')
buffer[1] = c.hour
buffer[2] = c.minute
buffer[3] = c.second
print("Sending time: " + str(buffer))
serial.write(buffer)
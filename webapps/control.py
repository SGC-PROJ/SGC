import serial
import time

#ser = serial.Serial("../../../dev/ttyACM0", 57600)
ser = serial.Serial("../../../dev/ttyUSB0", 57600)
time.sleep(2)

def flash():
    while(True):
        cmd = input()
        #All motor control
        if cmd == 'w':
            ser.write(b'W')
        if cmd == 'a':
            ser.write(b'A')
        if cmd == 's':
            ser.write(b'S')
        if cmd == 'd':
            ser.write(b'D')
        if cmd == 'p':
            ser.write(b'P')
        if cmd == 'j':
            ser.write(b'J')
        if cmd == 'k':
            ser.write(b'K')
        if cmd == 'q':
            ser.write(b'Q')
        if cmd == 'e':
            ser.write(b'E')
        if cmd == 'x':
            ser.write(b'X')
        if cmd == 'u':
            ser.write(b'U')
        if cmd == 'i':
            ser.write(b'I')
flash()
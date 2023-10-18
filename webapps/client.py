import serial
import time

def main():
    ser = serial.Serial("../../../dev/ttyUSB0", baudrate = 57600, timeout=None)
    while True:
       line = ser.readline().decode('utf-8').strip()
       print(line)

if __name__ == "__main__":
    main()
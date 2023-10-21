
import serial
import socket
import time

#for serial
#ser = serial.Serial("../../../dev/ttyACM0", 57600)
ser = serial.Serial("../../../dev/ttyUSB0", 57600)

server_ip = '192.168.239.42'
server_port = 12345

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((server_ip, server_port))

def main():
    while True:
        data = client_socket.recv(1024)
        if data:
            print("수신한 데이터:", data.decode())

            if data.decode() == 't':
                ser.write(b't')
                break;
            elif data.decode() == 'g':
                ser.write(b'g')
                break;
            elif data.decode() == 'p':
                ser.write(b'p')
                break;
            elif data.decode() == 'm':
                ser.write(b'm')
                break;
        
    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            client_socket.send(line.encode())
            print("success")
            break;
    
    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            print(line)
            main()
        
  
if __name__ == '__main__':
    main()
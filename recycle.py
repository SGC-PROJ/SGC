import time
import serial
import os
import realserver
import socket

ser = serial.Serial("../../../dev/ttyACM0", 57600)
os.environ['DISPLAY'] = ':0'
server_ip = '192.168.239.42'
server_port = 12345

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((server_ip, server_port))
server_socket.listen(1)
print("서버 대기 중...")
client_socket, client_address = server_socket.accept()
print("클라이언트가 연결되었습니다:", client_address)
def recycle(detect):
    if detect == 0:
        stuff = 'UNKNOwN'
    elif detect == 1:
        stuff = 'General Trash'
    elif detect == 2:
        stuff = 'Paper'
    elif detect == 3:
        stuff = 'Paper pack'
    elif detect == 4:
        stuff = 'Metal'
    elif detect == 5:
        stuff = 'Glass'
    elif detect == 6:
        stuff = 'Plastic'
    elif detect == 7:
        stuff = 'Styrofoam'
    elif detect == 8:
        stuff = 'Plastic bag'
    elif detect == 9:
        stuff = 'Bettery'
    elif detect == 10:
        stuff = 'Clothing'
    else:
        stuff = 'UNKNOwN'
    print(detect)
    print(f'detect = {detect}, stuff = {stuff}')
    if detect == 0 or detect == 1 or detect == 2 or detect == 3 or detect == 7 or detect == 8 or detect == 9 or detect == 10: #일쓰
        ser.write(b't')
        ti = 't'
        time.sleep(5)
    elif detect == 6: #플라스틱
        ser.write(b'p')
        ti = 'p'
        time.sleep(5)
    elif detect == 4: #철,캔
        ser.write(b'm')
        ti = 'm'
        time.sleep(5)
    elif detect == 5: #유리
        ser.write(b'g')
        ti = 'g'
        time.sleep(5)

    line = ser.readline()  # <3
    data = str(line)
    data = data.split('\'')
    data = str(data[1])
    data = data.split('\\')
    print(data[0])
    distance=int(data[0])
    time.sleep(5)

    if distance < 40:
        
    
        message = ti
        client_socket.send(message.encode())

        while True:
                # message=input()
                # client_socket.send(message.encode())
        
                data = client_socket.recv(1024)
                if data.decode() == 'end':
                    print("서버 응답:", data.decode())
                    break
                    time.sleep(1)
        
                print("서버 응답:", data.decode())
        

    '''
    if detect == 0:
        detect = 'UNKNOwN'
    elif detect == 1:
        detect = 'General Trash'
    elif detect == 2:
        detect = 'Paper'
    elif detect == 3:
        detect = 'Paper pack'
    elif detect == 4:
        detect = 'Metal'
    elif detect == 5:
        detect = 'Glass'
    elif detect == 6:
        detect = 'Plastic'
    elif detect == 7:
        detect = 'Styrofoam'
    elif detect == 8:
        detect = 'Plastic bag'
    elif detect == 9:
        detect = 'Bettery'
    elif detect == 10:
        detect = 'Clothing'
    else:
        detect = 'UNKNOwN'
    print(detect)
    
    port = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=None)
    if detect == 0: #Unknown
        port.write(b'0')
    elif detect ==1: #'General Trash'
        port.write(b'1')
    elif detect ==2: #'Paper'
        port.write(b'2')
    elif detect ==3: #'Paper pack'
        port.write(b'3')
    elif detect ==4:#'Metal'
        port.write(b'4')
    elif detect ==5:#'Glass'
        port.write(b'5')
    elif detect ==6:#'Plastic'
        port.write(b'6')
    elif detect ==7:#'Styrofoam'
        port.write(b'7')
    elif detect ==8:# 'Plastic bag'
        port.write(b'8')
    elif detect ==9:#'Bettery'
        port.write(b'9')
    elif detect ==10:#'Clothing'
        port.write(b'10')
    else:
        port.write(b'0')
        '''
    # print(detect)
import time
import serial
import os
import pygame

plastic = "sgc_sound/plastic.wav"
complete = "sgc_sound/complete.wav"
change = "sgc_sound/change.wav"
glass = "sgc_sound/glass.wav"
metal = "sgc_sound/metal.wav"
general = "sgc_sound/general.wav"
SGC = "sgc_sound/SGC.wav"
pygame.init()
pygame.display.set_mode((1, 1))
ser = serial.Serial("../../../dev/ttyACM0", 57600)
os.environ["DISPLAY"] = ":0"

def recycle(detect, client_socket):
    if detect == 0:
        stuff = "UNKNOwN"
    elif detect == 1:
        stuff = "General Trash"
    elif detect == 2:
        stuff = "Paper"
    elif detect == 3:
        stuff = "Paper pack"
    elif detect == 4:
        stuff = "Metal"
    elif detect == 5:
        stuff = "Glass"
    elif detect == 6:
        stuff = "Plastic"
    elif detect == 7:
        stuff = "Styrofoam"
    elif detect == 8:
        stuff = "Plastic bag"
    elif detect == 9:
        stuff = "Bettery"
    elif detect == 10:
        stuff = "Clothing"
    else:
        stuff = "UNKNOwN"
    print(detect)
    print(f"detect = {detect}, stuff = {stuff}")
    if (
        detect == 0
        or detect == 1
        or detect == 2
        or detect == 3
        or detect == 7
        or detect == 8
        or detect == 9
        or detect == 10
    ):  # 일쓰
        ser.write(b"t")
        ti = "t"
        pygame.mixer.music.load(general)
        pygame.mixer.music.play()
        while pygame.mixer.music.get_busy():
            pygame.time.Clock().tick(10)
        time.sleep(5)

    elif detect == 6:  # 플라스틱
        ser.write(b"p")
        ti = "p"
        pygame.mixer.music.load(plastic)
        pygame.mixer.music.play()
        while pygame.mixer.music.get_busy():
            pygame.time.Clock().tick(10)
        time.sleep(5)
        
    elif detect == 4:  # 철,캔
        ser.write(b"m")
        ti = "m"
        pygame.mixer.music.load(metal)
        pygame.mixer.music.play()
        while pygame.mixer.music.get_busy():
            pygame.time.Clock().tick(10)
        time.sleep(5)

    elif detect == 5:  # 유리
        ser.write(b"g")
        ti = "g"
        pygame.mixer.music.load(glass)
        pygame.mixer.music.play()
        while pygame.mixer.music.get_busy():
            pygame.time.Clock().tick(10)
        time.sleep(5)

    line = ser.readline()  # <3
    data = str(line)
    data = data.split("'")
    data = str(data[1])
    data = data.split("\\")
    print(data[0])
    distance = int(data[0])
    time.sleep(5)

    if distance < 35:
        message = ti
        client_socket.send(message.encode())
        pygame.mixer.music.load(complete)
        pygame.mixer.music.play()
        while pygame.mixer.music.get_busy():
            pygame.time.Clock().tick(10)

        while True:
            # message=input()
            # client_socket.send(message.encode())

            data = client_socket.recv(1024)
            if data.decode() == "end":
                print("서버 응답:", data.decode())
                pygame.mixer.music.load(complete)
                pygame.mixer.music.play()
                while pygame.mixer.music.get_busy():
                    pygame.time.Clock().tick(10)
                break
                time.sleep(1)

            print("서버 응답:", data.decode())

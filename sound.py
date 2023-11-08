import pygame
import serial

ser = serial.Serial("../../../dev/ttyACM0", 57600)


def sound():
    pygame.init()

    SGC = "sgc_sound/SGC.wav"
    ser.write(b"b")

    line = ser.readline().decode("utf-8").strip()

    if line == "y":
        pygame.display.set_mode((1, 1))
        pygame.mixer.music.load(SGC)
        pygame.mixer.music.play()
        while pygame.mixer.music.get_busy():
            pygame.time.Clock().tick(10)
    else:
        return

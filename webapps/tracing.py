"""
Experiment stages

camera → motorTest → control → sever & client → transfer → tracing
"""

import cv2 #OpenCV를 사용하기위해 import해줍니다.
import numpy as np #파이썬의 기본 모듈중 하나인 numpy
import serial
import time


#for serial
#ser = serial.Serial("../../../dev/ttyACM0", 57600)
ser = serial.Serial("../../../dev/ttyUSB0", 57600)

#wait for settings
time.sleep(2)
# 1920 X 1080
def letsgo():
    camera = cv2.VideoCapture(-1) #카메라를 비디오 입력으로 사용. -1은 기본설정이라는 뜻
    width = camera.get(cv2.CAP_PROP_FRAME_WIDTH)        # 640
    height = camera.get(cv2.CAP_PROP_FRAME_HEIGHT)      # 480
    
    while( camera.isOpened() ): #카메라가 Open되어 있다면,
        ret, frame = camera.read() #비디오의 한 프레임씩 읽습니다. ret값이 True, 실패하면 False, fram에 읽은 프레임이 나옴
        #frame = cv2.flip(frame,-1) #카메라 이미지를 flip, 뒤집습니다. -1은 180도 뒤집는다
        # cv2.imshow( 'normal' , frame)  #'normal'이라는 이름으로 영상을 출력
        
        crop_img = frame[0:480, int((width / 2))- 300:int((width / 2))+ 300]
        crop_img2 = frame[0:240, int((width / 2))- 300:int((width / 2))+ 300]
        crop_img3 = frame[240:480, int((width / 2))- 300:int((width / 2))+ 300]
        
        frame = frame[0:480, int((width / 2))- 300:int((width / 2))+ 300]
        
        
        # 흑백 영상 출력
        gray_b = cv2.cvtColor(crop_img, cv2.COLOR_BGR2GRAY) #이미지를 회색으로 변경
        
        blur_b = cv2.GaussianBlur(gray_b, (5,5) , 0) #가우시간 블러로 블러처리를 한다.
        
        th = 60
        ret,thresh1_b = cv2.threshold(blur_b, th, 255, cv2.THRESH_BINARY_INV) #임계점 처리로, 123보다 크면, 255로 변환
        #123밑의 값은 0으로 처리한다. 흑백으로 색을 명확하게 처리하기 위해서
        
        # cv2.imshow('thresh1_b' ,thresh1_b)  #처리된 영상인 thresh1을 출력한다.
            #이미지를 압축해서 노이즈를 없앤다.
        mask_b = cv2.erode(thresh1_b, None, iterations=2)  
        mask_b = cv2.dilate(mask_b, None, iterations=2)
        cv2.imshow('mask',mask_b)
        
        
        
        # 상단 crop_img 무게중심
                            #frame
        gray = cv2.cvtColor(crop_img2, cv2.COLOR_BGR2GRAY) #이미지를 회색으로 변경
        
        blur = cv2.GaussianBlur(gray, (5,5) , 0) #가우시간 블러로 블러처리를 한다.
        
        th = 60
        ret,thresh1 = cv2.threshold(blur, th, 255, cv2.THRESH_BINARY_INV) #임계점 처리로, 123보다 크면, 255로 변환
        #123밑의 값은 0으로 처리한다. 흑백으로 색을 명확하게 처리하기 위해서
        
        # cv2.imshow('thresh1' ,thresh1)  #처리된 영상인 thresh1을 출력한다.
            #이미지를 압축해서 노이즈를 없앤다.
        mask = cv2.erode(thresh1, None, iterations=2)  
        mask = cv2.dilate(mask, None, iterations=2)
        # cv2.imshow('mask',mask)
    
        #이미지의 윤곽선을 검출
        contours,hierarchy = cv2.findContours(mask.copy(), 1, cv2.CHAIN_APPROX_NONE)
        
        #윤곽선이 있다면, max(가장큰값)을 반환, 모멘트를 계산한다.
        if len(contours) > 0:
            c = max(contours, key=cv2.contourArea)
            M = cv2.moments(c)
             
            #X축과 Y축의 무게중심을 구한다.
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])
            
            # frame = cv2.rectangle(frame, (cx,0), ())
            
           #X축의 무게중심을 출력한다.
            frame = cv2.line(frame,(cx, cy-10),(cx,cy+10),(255,0,0),1)
            frame = cv2.line(frame,(cx-10, cy),(cx+10, cy),(255,0,0),1)

            # cv2.imshow( 'normal' , frame)  #'normal'이라는 이름으로 영상을 출력
        
            cv2.drawContours(frame, contours, -1, (0,255,0), 1)
            
        # 하단 crop_img 무게중심
                            #frame
        gray2 = cv2.cvtColor(crop_img3, cv2.COLOR_BGR2GRAY) #이미지를 회색으로 변경
        
        blur2 = cv2.GaussianBlur(gray2, (5,5) , 0) #가우시간 블러로 블러처리를 한다.
        
        ret2,thresh2 = cv2.threshold(blur2, th, 255, cv2.THRESH_BINARY_INV) #임계점 처리로, 123보다 크면, 255로 변환
        #123밑의 값은 0으로 처리한다. 흑백으로 색을 명확하게 처리하기 위해서
        
        # cv2.imshow('thresh1' ,thresh2)  #처리된 영상인 thresh1을 출력한다.
            #이미지를 압축해서 노이즈를 없앤다.
        mask2 = cv2.erode(thresh2, None, iterations=2)  
        mask2 = cv2.dilate(mask2, None, iterations=2)
        # cv2.imshow('mask',mask2)
    
        #이미지의 윤곽선을 검출
        contours2,hierarchy = cv2.findContours(mask2.copy(), 1, cv2.CHAIN_APPROX_NONE)
        
        #윤곽선이 있다면, max(가장큰값)을 반환, 모멘트를 계산한다.
        if len(contours2) > 0:
            ca = max(contours2, key=cv2.contourArea)
            Ma = cv2.moments(ca)
             
            #X축과 Y축의 무게중심을 구한다.
            cx2 = int(Ma['m10']/Ma['m00'])
            cy2 = int(Ma['m01']/Ma['m00']) + 240
            
            # frame = cv2.rectangle(frame, (cx,0), ())
            
           #X축의 무게중심을 출력한다.
            frame2 = cv2.line(frame,(cx2, cy2-10),(cx2,cy2+10),(255,0,0),1)
            frame2 = cv2.line(frame,(cx2-10, cy2),(cx2+10, cy2),(255,0,0),1)
            # cv2.drawContours(frame2, contours2, -1, (0,255,0), 1)

            cv2.imshow( 'normal' , frame2)  #'normal'이라는 이름으로 영상을 출력
        
            
            
            dif = cx-cx2
            
            doMotor(dif)
            #print(cx-cx2) #출력값을 print 한다.
            
        if cv2.waitKey(1) == ord('p'): #만약 q라는 키보드값을 읽으면 종료합니다.
            ser.write(b'p')
            exit(1)
        
    cv2.destroyAllWindows() #이후 openCV창을 종료합니다.

value = 80

def doMotor(cx):
    #Straight
    if cx >= -1 * value and cx < value:
        print(cx, "  w")
        ser.write(b'w')
    #Left
    elif cx < -1 * value  and cx <= -200 :
        print(cx, "  a")
        ser.write(b'a')
    #right
    elif cx >= value and cx <= 200:
        print(cx, ' d')
        ser.write(b'd')
    else:
        ser.write(b'p')



def main():
    ser.write(b'u')
    #ser.write(b'i')
    letsgo()
    # while True:
    #     data = client_socket.recv(1024)
    #     if not data:
    #         print("receive nothing")
    #     print("수신한 데이터:", data.decode())
    #     client_socket.send("데이터 수신 완료".encode())
    #     cx = data.decode()
    #     doMotor(cx)
    
if __name__ == '__main__':
    main()




# Line Tracing Link = https://chick-it.tistory.com/20?category=1074980
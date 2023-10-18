import cv2   #OpenCV를 사용하기위해 import해줍니다.

def main():
    camera = cv2.VideoCapture(-1) #카메라를 비디오 입력으로 사용. -1은 기본설정이라는 뜻
    camera.set(3,1280)  #띄울 동영상의 가로사이즈 640픽셀
    camera.set(4,960)  #세로사이즈 480픽셀
    desired_fps = 30  # 원하는 프레임 레이트로 변경하세요.
    camera.set(cv2.CAP_PROP_FPS, desired_fps)
    
    camera.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'MJPG'))
    while( camera.isOpened() ):  #카메라가 Open되어 있다면,
        _, image = camera.read()  ##비디오의 한 프레임씩 읽습니다. _값이 True, 실패하면 False, image에 읽은 프레임이 나옴
        image = cv2.flip(image,-1)  #카메라 이미지를 flip, 뒤집습니다. -1은 180도 뒤집는다는 뜻입니다.
        cv2.imshow( 'camera test' , image)  #카메라를 'camera test'라는 이름의 파일로 보여줍니다. 
        


        
        if cv2.waitKey(1) == ord('q'):  #만약 q라는 키보드값을 읽으면 종료합니다.
            break
        
    cv2.destroyAllWindows() #이후 openCV창을 종료합니다.
    
if __name__ == '__main__':
    main()
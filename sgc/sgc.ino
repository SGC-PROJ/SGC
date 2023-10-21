#include <Servo.h>
Servo myservo;         
//motor control pin
const int IN1 = 26; // L298 Input 1 / dir #28번홀 고장
const int IN2 = 29; // L298 Input 2 / pwm
#define trig1 9 //엔코더 모터 반대편 초음파센서
#define echo1 8
#define trig2 7 //엔코더 모터쪽 초음파센서
#define echo2 6
int pos = 0;                                               // 모터 위치를 확인하기 위해 변수를 선언
int servoPin = 4;  
#define ENA 10

#define POWER 200

void setup() {
  Serial.flush();
 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode (servoPin, OUTPUT);           // 모터 제어핀을 출력으로 설정
  myservo.attach(servoPin);                                // 모터의 신호선을 12번핀에 연결

  Serial.begin(57600);
}

void loop() {
  if(Serial.available()){
    char cmd = Serial.read();
    myservo.write(95);

    if (cmd == 'a'){  // 랙앤피니언 모터 테스트(default 반대 방향)
      digitalWrite(IN2, HIGH);
      digitalWrite(IN1, LOW);
      analogWrite(ENA, POWER);
      delay(2600);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
    }

    if (cmd == 'd'){   // 랙앤피니언 모터 테스트(default)
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, POWER);
      delay(2600);          // 모터 딜레이
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);      
    }

    if (cmd == 'q'){    // 초음파 1번 테스트
      digitalWrite(trig1, HIGH);
      //delayMicroseconds(10);
      digitalWrite(trig1, LOW);
      int distance = pulseIn(echo1, HIGH) * 17 / 1000;
      Serial.println(distance);
    }

    if (cmd == 'e'){    // 초음파 2번 테스트
      digitalWrite(trig2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig2, LOW);
      int distance = pulseIn(echo2, HIGH) * 17 / 1000;
      Serial.println(distance);
    }

    if(cmd == 't'){   // 일반쓰레기, 엔코더 모터 작동 후 1번 센서쪽으로 기울임
      digitalWrite(IN2, HIGH);
      digitalWrite(IN1, LOW);
      analogWrite(ENA, POWER);
      delay(2600);          // 모터 딜레이
      digitalWrite(IN2, LOW);
      digitalWrite(IN1, LOW);
      analogWrite(ENA, 0);  // 랙앤피니언 모터 이동 종료
    
      myservo.write(15);
      delay(1000);          // 서보 딜레이
      myservo.write(95);

      delay(500);           // 초음파 측정 전 안정화 딜레이
      digitalWrite(trig1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig1, LOW);
      int distance = pulseIn(echo1, HIGH) * 17 / 1000;
      Serial.println(distance);
      delay(500);           // 초음파 측정후 안정화 딜레이

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, POWER);
      delay(2600);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
    }

    if(cmd == 'p'){   //플라스틱 엔코더 모터 작동후 2번 센서쪽으로 기울임
      digitalWrite(IN2, HIGH);
      digitalWrite(IN1, LOW);
      analogWrite(ENA, POWER);
      delay(2600);          // 모터 딜레이
      digitalWrite(IN2, LOW);
      digitalWrite(IN1, LOW);
      analogWrite(ENA, 0);  // 랙앤피니언 모터 이동 종료
      
      myservo.write(175);
      delay(1000);          // 서보 딜레이
      myservo.write(95);

      delay(500);           // 초음파 측정 전 안정화 딜레이
      digitalWrite(trig2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig2, LOW);
      int distance = pulseIn(echo2, HIGH) * 17 / 1000;
      Serial.println(distance);
      delay(500);           // 초음파 측정후 안정화 딜레이

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, POWER);
      delay(2600);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
    }

    if(cmd=='m'){   //캔,철,금속류 디폴트 위치에서 1번 센서로 기울임
      myservo.write(15);
      delay(1000);
      myservo.write(95);
      
      delay(500);           // 초음파 측정 전 안정화 딜레이
      digitalWrite(trig1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig1, LOW);
      int distance = pulseIn(echo1, HIGH) * 17 / 1000;
      Serial.println(distance);
      delay(500);           // 초음파 측정후 안정화 딜레이
      
    }

    if(cmd=='g'){   //유리 디폴트 위치에서 2번 센서로 기울임
      myservo.write(175);
      delay(1000);
      myservo.write(95);

      delay(500);           // 초음파 측정 전 안정화 딜레이
      digitalWrite(trig2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig2, LOW);
      int distance = pulseIn(echo2, HIGH) * 17 / 1000;
      Serial.println(distance);
      delay(500);           // 초음파 측정후 안정화 딜레이
    }
  }
}

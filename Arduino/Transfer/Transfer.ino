//right front (1)
#define ENA 6
#define IN1 36
#define IN2 34

//left front (2)
#define ENB 4
#define IN3 32
#define IN4 30

//left rear  (3)
#define ENC 3   //ENA
#define IN5 28  //IN1
#define IN6 26  //IN2

//right rear (4)
#define END 2   //ENB
#define IN7 24  //IN3
#define IN8 22  //IN4

//Analog Signal CONTROL(POWER)
int c = 80;

//Relay → with NC
#define S1 42 //back
#define S2 40 //front

//IR Sensor
//Head
#define HR A8   //L
#define HC A10  //C
#define HL A12  //R

//rear
#define RR A9   //L
#define RC A14  //C
#define RL A15  //R

//motor control values for
int SR=1, SC=1, SL=1;   //hold state
int d=1;                //head or rear sensor
int state=0;            //cross line processing
int L, R, C;            //read IR sensor
int go = 0;             //start or stop



void print(int d, int state, int L, int C, int R){
  char dir = (d==1)?'f':'b';
  Serial.print(state);
  Serial.print(": ");
  Serial.print(L);
  Serial.print(" ");
  Serial.print(C);
  Serial.print(" ");
  Serial.print(R);
  Serial.print(" / ");
  Serial.println(dir);
  if (L == 1 && C == 1 && R == 1){
    Serial.println("----------------------------");
  }
}

void straight(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, c);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, c+15);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(ENC, c);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(END, c+15);
}

void left(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, c-15);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, c);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(ENC, c+15);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(END, c+30);
}

void right(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, c+15);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, c+30);     
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(ENC, c-15);        //c-20
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  analogWrite(END, c);        //c-5
}

void back(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, c);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, c+15);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(ENC, c);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  analogWrite(END, c+15);
}

//rotate
void clockWise(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, c);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, c+15);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(ENC, c);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  analogWrite(END, c+15);
}

void counterClockWise(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, c);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, c+15);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(ENC, c);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(END, c+15);
}

void backRight(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, c+30);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, c+15);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(ENC, c-10);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  analogWrite(END, c-25);
}

void backLeft(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, c-10);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, c-25);     
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(ENC, c+30);        //c-20
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  analogWrite(END, c+15);        //c-5
}

void stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
    
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);

  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
  analogWrite(ENC, 0);

  digitalWrite(IN7, LOW);
  digitalWrite(IN8, LOW);
  analogWrite(END, 0);
}
  
//cross line processing
void crossLine(int n, int state){
  switch(state){
    case 1:
      switch(n){
        case 1:
          straight();
          break;
        case 2:
          right();
          break;
        case 3:
          straight();
        case 4:
          left();
          break;
      }
    break;
    case 2:
     switch(n){
        case 1:
          left();
          break;
        case 2:
          stop();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          digitalWrite(S2, HIGH);
          d=0;
          delay(500);
          break;
        case 3:
          left();
          break;
        case 4:
          stop();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          digitalWrite(S2, HIGH);
          d=0;
          delay(500);
          break;
      }  
    break;
    case 3:
      switch(n){
        case 1:
          stop();
          delay(500);
          d=0;
          delay(500);
          back();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          break;
        case 2:
          back();
          break;
        case 3:
          stop();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          break;
        case 4:
          straight();
          break;
      }
    break;
    case 4:
      switch(n){
        case 1:
          back();
          break;
        case 2:
          backRight();
          break;
        case 3:
          stop();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          break;
        case 4:
          straight();
          break;
      }
    break;
    case 5:
      switch(n){
        case 1:
          backRight();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          break;
        case 2:
          straight();
          break;
        case 3:
          stop();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          break;
        case 4:
          straight();
          break;
      }
    break;
    case 6:
      switch(n){
        case 1:
          back();
          break;
        case 2:
          straight();
          break;
        case 3:
          stop();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          break;
        case 4:
          straight();
          break;
      }
    break;
    case 7:
      switch(n){
        case 1:
          backLeft();
          break;
        case 2:
          straight();
          break;
        case 3:
          stop();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          break;
        case 4:
          straight();
          break;
      }
    break;
    case 8:
      switch(n){
        case 1:
          back();
          break;
        case 2:
          straight();
          break;
        case 3:
          stop();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          break;
        case 4:
          straight();
          break;
      }
    break;
    case 9:
      switch(n){
        case 1:
          stop();
          delay(1000);
          break;
        case 2:
          straight();
          break;
        case 3:
          stop();                   //시점 변경부분 실험하며 좀 더 자연스럽게 편집
          break;
        case 4:
          straight();
          break;
      }
    break;
    
    default:
      Serial.println("out of range");
      stop();
      delay(99999);
      break;
  }
}

void setup() {
  Serial.begin(57600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENC, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);

  pinMode(END, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);

  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
    
  //Relay initial setting(off)
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);

  Serial.println("=========================================");
}

/*
      front
2(N)        1(R)
3(N)        4(R)
      rear

Notice) M+ and M- of motor1, 4 are connected by OUT2 and OUT1 (reverse connection)
*/

void loop() {   
  if(Serial.available()){
    char cmd = Serial.read();

    switch(cmd){
      case 't':
      //general trash
        go = 1;
        break;
      case 'g':
      //glass
        go = 2;
        break;
      case 'p':
      //plastic
        go = 3;
        break;
      case 'm':
      //metal
        go = 4;
        break;
      }
    
  }//position direction
  
  //L,C,R = 1(HIGH) → black → turn off
  //L,C,R = 0(LOW) → white → turn on
  if(d == 1){
    L = digitalRead(HR);
    C = digitalRead(HC);
    R = digitalRead(HL);
  }
  else{
    L = digitalRead(RR);
    C = digitalRead(RC);
    R = digitalRead(RL);
  }

  if(go){
    //Hold --- 0 0 0
    if ( L == LOW && C == LOW && R == LOW ) {    
      L = SL; 
      C = SC; 
      R = SR;
    }
    //Straight --- 0 1 0
    else if( L == LOW && C == HIGH && R == LOW ){     
      if(d==1) straight();
      else back();
    }
    //Left --- 1 0 0
    else if(L == HIGH && C == LOW && R == LOW ){
      if(d==1) left();
      else backLeft();
    }
    //Left corner --- 1 1 0
    else if(L == HIGH && C == HIGH && R == LOW ){
      if(d==1) counterClockWise();
      else clockWise();
    }
    //Right --- 0 0 1, 0 1 1
    else if(L == LOW && C == LOW && R == HIGH ){
      if(d==1) right();
      else backRight();
    } 
    //Right corner --- 0 1 1
    else if(L == LOW && C == HIGH && R == HIGH ){
      if(d==1) clockWise();
      else counterClockWise();
    } 
    //Pause --- 1 1 1
    if( L == HIGH && C==HIGH && R == HIGH ){
      print(d, state, L, C, R);
      clockWise();
      L, C, R = 0;
      delay(1500);
      if(d == 1){
        L = digitalRead(HR);
        C = digitalRead(HC);
        R = digitalRead(HL);
      }
      else{
        L = digitalRead(RR);
        C = digitalRead(RC);
        R = digitalRead(RL);
      }
      // if((L==SL)&&(C==SC)&&(R==SR))   {//same cross line
      //   crossLine(go, state);
      // }
      // else{                           //new cross line
      //   state += 1;
      //   crossLine(go, state);  
      // }
    }

    //print IR
    if (L != SL || C != SC || R != SR){
      print(d, state, L, C, R);
    }
    SL = L; SC = C; SR = R;
   }

}//end of loop

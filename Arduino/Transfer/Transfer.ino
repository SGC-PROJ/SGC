//right front (1)
#define ENA 
#define IN1 28
#define IN2 29

//left front (2)
#define ENB 
#define IN3 30
#define IN4 31

//left rear  (3)  //another driver
#define ENC      //ENA
#define IN5 32    //IN1
#define IN6 33    //IN2

//right rear (4)
#define END     //ENB
#define IN7 34   //IN3
#define IN8 35   //IN4

//Analog Signal CONTROL(POWER)
#define CONTROL 70

//Relay → with NC
#define S1 43
#define S2 49

//IR Sensor
#define IR1 A8  //L
#define IR2 A10  //C
#define IR3 A12 //R

//arrive siganl
#define ARRIVE 38

//values for
bool logging = true;    //recording
int s1 = 1, s2 = 1;     //electonical magnet
int SR=1, SC=1, SL=1;   //hold state


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
  

void doMotor(){
   while(1){
    //L,C,R = 1(HIGH) → black → turn off
    //L,C,R = 0(LOW) → white → turn on
    int L = digitalRead(IR1);
    int C = digitalRead(IR2);
    int R = digitalRead(IR3);
    
    //Hold --- 0 0 0
    if ( L == LOW && C == LOW && R == LOW ) {    
      L = SL; C = SC; R = SR;
    }
    //Straight --- 0 1 0
    else if( L == LOW && C == HIGH && R == LOW ){     
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, CONTROL);
        
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, CONTROL);

      digitalWrite(IN5, HIGH);
      digitalWrite(IN6, LOW);
      analogWrite(ENC, CONTROL);

      digitalWrite(IN7, HIGH);
      digitalWrite(IN8, LOW);
      analogWrite(END, CONTROL);

      logging = true; 
    }
    //Left --- 1 0 0, 1 1 0
    else if(L == HIGH && R == LOW ){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, CONTROL);
        
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, CONTROL);

      digitalWrite(IN5, LOW);
      digitalWrite(IN6, HIGH);
      analogWrite(ENC, CONTROL);

      digitalWrite(IN7, HIGH);
      digitalWrite(IN8, LOW);
      analogWrite(END, CONTROL);

      logging = true; 
    }
    //Right --- 0 0 1, 0 1 1
    else if(L == LOW && R == HIGH){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, CONTROL);
        
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, CONTROL);

      digitalWrite(IN5, HIGH);
      digitalWrite(IN6, LOW);
      analogWrite(ENC, CONTROL);

      digitalWrite(IN7, LOW);
      digitalWrite(IN8, HIGH);
      analogWrite(END, CONTROL);

      logging = true; 
    }
    //Pause --- 1 1 1 or 1 0 1 
    if( L == HIGH && R == HIGH ){
      stop();
      return;
    } 

    //hold position
    SL = L; SC = C; SR = R;
   }//end of while
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

  pinMode(ARRIVE, OUTPUT);    

  //Relay initial setting(off)
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
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
    if(cmd == 't'){
      //lotate
    }
    else if(cmd == 'g')
    {
      //lotate
    }
    else if(cmd == 'p'){
      //lotate
    }
    else if(cmd == 'm'){
      //lotate
    }
  
  }//end of serial
  
  doMotor();
  delay(1000);
  Serial.println("end");

  //transfer and return
  /*
  doMotor
  delay(1000);
  Serial.println("success");
  */


}//end of loop

#include <Servo.h>
#include <AFMotor.h>


//String command;

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

const int trigpin = A1;
const int echopin = A0;

String command;

Servo myservo;
int pos=0;

long duration;
int distanceCm = 0;
int distanceHold = 20;
boolean rightObject , leftObject , lastTurn;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  myservo.attach(10);
  myservo.write(90);

}

void loop() 
{
  distanceCm = getDistance();
  Serial.println(distanceCm);

  if( distanceCm <= distanceHold)
  {
    Stop();
  }



  if(Serial.available()) {
    command = "";  
    command = Serial.readString();
  
    Serial.print(command);
    
    //Serial.println(distanceCm);

    if(command[0] == 'F' && distanceCm > distanceHold){
      Serial.println(distanceCm);
      forward(); 
    }
    else if(command == "*move forward#" || command == "*Move forward#" || command == "*move forwards#" ){
      if(distanceCm > distanceHold)
      {
        voiceforward();
      }
  
    }
    else if(command == "*move backward#" || command == "*Move backward#" || command == "*move backwards#"){
      if(distanceCm > distanceHold)
      {
        voicebackward();
      }
    
    }




    else if(command == "*turn left#" || command == "*Turn left#"){
      myservo.write(180);
      delay(2000);    
      if( distanceCm > distanceHold){
        myservo.write(90);
        voiceleft();
      }else{
        myservo.write(90);
        Stop();
      }    
    }
    else if(command == "*turn right#" || command == "*Turn right#"){
      myservo.write(0);
      delay(2000);    
      if( distanceCm > distanceHold){
        myservo.write(90);
        voiceright();
      }else{
        myservo.write(90);
        Stop();
      } 
    }
    
    
    else if(command == "*stop#"){
    Stop();
    
    }
    else if(command[0] == 'V'){
      Stop();
    }
    else if(command[0] == 'B' ){
    backward();
    }
    else if(command[0] == 'L'){
      myservo.write(180);
      delay(2000);    
      if( distanceCm > distanceHold){
        myservo.write(90);
        left();
      }else{
        myservo.write(90);
        Stop();
      }    
   }
   else if(command[0] == 'R'){
    myservo.write(0);
    delay(2000);    
    if( distanceCm > distanceHold){
      myservo.write(90);
      right();
    }else{
      myservo.write(90);
      Stop();
    }
  }else{
    Stop();
  }

  
  if( getDistance() <= distanceHold){
    Stop();
  }
  //command = "";
  
 }
}





// functions

void voiceforward() {
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
}

void forward() {
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  }

void voicebackward() {
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  
}

void backward() {
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  
  
  }


void voiceleft() {
  
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  
}

void left() {
 
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  
  
  
}

void right() {
  
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  
  
}

void voiceright() {
  
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);

}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

int getDistance(){
  int echoTime;
  int calDistnce;

  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

  echoTime = pulseInLong(echopin, HIGH);

  calDistnce = echoTime / 60;
  return calDistnce;
}
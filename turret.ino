/* Sweep
 *  UPDATED 4:13 PM WED
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

//Last Updated 00:58. Wednesday

#include <Servo.h>
#include <NewPing.h>

Servo myServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

//int pos = 0;    // variable to store the servo position
/// Code written for CSE331 project: Microprocessor Interfacing
/// Group members are ---
/// ASIF HAIDER KHAN   |   1421341042
//  DEBRAJ SAHA DIPTA  |   1520537642

#define TrigA 4
#define EchoA 3
#define TrigB 5
#define EchoB 6
#define TrigC 7
#define EchoC 8
#define MAX_DIST 15
#define LEDpin 36
#define LEDgnd 37
#define LED2vcc 52
#define LED2gnd 53
#define buzzV 41
#define buzzG 46

NewPing sonarA(TrigA,EchoA,MAX_DIST);
NewPing sonarB(TrigB,EchoB,MAX_DIST);
NewPing sonarC(TrigC,EchoC,MAX_DIST);

int angle = 0;

int count = 0;

int readSonarA(){
  int dist = 0;
  dist = sonarC.ping_cm();
  if(dist == 0 || dist > MAX_DIST){
    return -1;
  }
  else{
    return dist;
  }
}

int readSonarB(){
  
  int dist = 0;
  delay(5);
  dist = sonarB.ping_cm();
  if(dist == 0 || dist > MAX_DIST){
    return -1;
  }
  else{
    return dist;
  }
}
int readSonarC(){
  int dist = 0;
  delay(5);
  dist = sonarC.ping_cm();
  if(dist == 0 || dist > MAX_DIST){
    return -1;
  }
  else{
    return dist;
  }
}

void warningON(){
  digitalWrite(LEDpin,HIGH);
  digitalWrite(LEDgnd,LOW);
  digitalWrite(buzzV,HIGH);
  digitalWrite(buzzG,LOW);
}
void warningOFF(){
  digitalWrite(LEDpin,LOW);
  digitalWrite(LEDgnd,LOW);
  digitalWrite(buzzV,LOW);
  digitalWrite(buzzG,LOW);
}
//int dist[3];
int a,b,c;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);  // attaches the servo on pin 9 to the servo object
  //CalibrateSonars();
  
  pinMode(LED2vcc,OUTPUT);
  pinMode(LED2gnd,OUTPUT);
  pinMode(LEDpin,OUTPUT);
  pinMode(LEDgnd,OUTPUT);
  pinMode(buzzV,OUTPUT);
  pinMode(buzzG,OUTPUT);
}
int Decode(int a, int b, int c){
  if(a != -1 && b != -1 && c != -1){
    return 1;
  }
  else{
    return 0;
  }
}
void loop() {
  //Left Sweep and Check
  //count = 0;
  
  if(angle >= 0 && angle < 180){
      a = readSonarA();
      b = readSonarB();
      c = readSonarC();
      int x = Decode(a,b,c);
      switch(x){
        case 0:
             count = 0;
             warningOFF();
              digitalWrite(LED2vcc,LOW);
              digitalWrite(LED2gnd,LOW);
             Serial.println("-----------NO OBJECT DETECTED-------------"); 
             myServo.write(angle);
             angle+=1;
             delay(15); break; 
        case 1:
             Serial.println("-----------OBJECT DETECTED-------------");
             warningON();  //Object Found
             count += 1;
             Serial.println(count);
             if( count > 15){
              Serial.println("-----------OBJECT IS STATIONARY-------------");
              digitalWrite(LED2vcc,HIGH);
              digitalWrite(LED2gnd,LOW);   
             }
             else{
              Serial.println("-----------OBJECT IS MOVING-------------");
              digitalWrite(LED2vcc,LOW);
              digitalWrite(LED2gnd,LOW);
             }
             break;
        default:
             count = 0;
             warningOFF();
             Serial.println("-----------NO OBJECT DETECTED-------------");
             digitalWrite(LED2vcc,LOW);
             digitalWrite(LED2gnd,LOW);
             myServo.write(angle);
             angle+=1;
             delay(15); break;
          
      }
      
  }
  
  else if(angle >= 180 && angle <= 360){
      a = readSonarA();
      b = readSonarB();
      c = readSonarC();
      int x = Decode(a,b,c);
      switch(x){
        case 0:
             count = 0;
             warningOFF();
             digitalWrite(LED2vcc,LOW);
             digitalWrite(LED2gnd,LOW);
             myServo.write(360 - angle);
             angle+=1;
             delay(15); break;
        case 1:
             Serial.println("-----------OBJECT DETECTED-------------");
             warningON();  //Object Found
             count += 1;
             Serial.println(count);
             if( count > 15){
              Serial.println("-----------OBJECT IS STATIONARY-------------");
              digitalWrite(LED2vcc,HIGH);
              digitalWrite(LED2gnd,LOW);   
             }
             else{
              Serial.println("-----------OBJECT IS MOVING-------------");
             } 
             break;
        default:
             count = 0;
             warningOFF();
             digitalWrite(LED2vcc,LOW);
             digitalWrite(LED2gnd,LOW);
             myServo.write(360 - angle);
             angle+=1;
             delay(15); break;
          
      }
        
  }
  else{
    angle = 0;
    //count = 0;
  }
}

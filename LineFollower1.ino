#include <QTRSensors.h>
#include "Servo.h"

#define DEFAULT_TURN           80
#define DEFAULT_TURN_BACK      70
#define NUM_SENSORS             4  
#define NUM_SAMPLES_PER_SENSOR  4  

Servo myservo;  
int pos = 20;

QTRSensorsAnalog qtra((unsigned char[]) {0, 1, 2, 3}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR);
unsigned int sensorValues[NUM_SENSORS];
int MOTOR1_PIN1 = 3;
int MOTOR1_PIN2 = 5;
int MOTOR2_PIN1 = 6;
int MOTOR2_PIN2 = 9;
int DEFAULT_WHITE = 100; 
int DEFAULT_BLACK = 500; 


void setup()
{ delay(500);
  myservo.attach(10);  
  myservo.write(pos);
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
 
 
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    
  for (int i = 0; i < 400; i++)  
  {
    qtra.calibrate();       
  }
  digitalWrite(13, LOW);     

  
  
  
  
 
}



void loop()
{ 
  int volts = analogRead(4);
  
  if (volts < 300)
  { if (pos>20)
  {  open();   }
  
  qtra.read(sensorValues);
  
  if (sensorValues[0] < 100 && sensorValues[3]< 100 && sensorValues[1] >500 || sensorValues[2]>500)
    go (50,50);
     
  if (sensorValues[0] >500 && sensorValues[3]<100)
    go(100, -100);
   
  if (sensorValues[0] <100 && sensorValues[3]> 500 )
         go(-100,100);
                 
  if (sensorValues[0]<100 && sensorValues[1] <100 && sensorValues[2] <100 && sensorValues[3]<100)
         go (-50,-50); 
         
  if (sensorValues[0]>500 && sensorValues[1] >500 && sensorValues[2] >500 && sensorValues[3]<100)
        go (100,-100);
        
  if (sensorValues[0]<100 && sensorValues[1] >500 && sensorValues[2] >500 && sensorValues[3]>500)
        go(-100,100);  }
         
       else {   go(0,0);
                delay(100);
                go(50,50);
                delay(200);
                go(0,0); 
                close() ;
                go(0,0);
                delay(400);
                go(DEFAULT_TURN,-DEFAULT_TURN);
                delay(500);   
                go(0,0);          
                open();   
                delay(500);
                go(-DEFAULT_TURN_BACK,DEFAULT_TURN_BACK);                     
                delay(500);
                go(0,0);
                delay(1000);                        
       }        
             
}

void go(int speedLeft, int speedRight) {
  if (speedLeft > 0) {
    analogWrite(MOTOR1_PIN1, speedLeft);
    analogWrite(MOTOR1_PIN2, 0);
  } 
  else {
    analogWrite(MOTOR1_PIN1, 0);
    analogWrite(MOTOR1_PIN2, -speedLeft);
  }
 
  if (speedRight > 0) {
    analogWrite(MOTOR2_PIN1, speedRight);
    analogWrite(MOTOR2_PIN2, 0);
  }else {
    analogWrite(MOTOR2_PIN1, 0);
    analogWrite(MOTOR2_PIN2, -speedRight);
  }
}

void close ()
         {  pos = 120;                               
            myservo.write(pos); }             
           
void open ()
         {  pos = 20;                               
            myservo.write(pos); }    

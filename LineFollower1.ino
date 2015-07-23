#include <QTRSensors.h>

#define NUM_SENSORS             4  
#define NUM_SAMPLES_PER_SENSOR  4  
#define EMITTER_PIN             2  
#include "Servo.h"

Servo myservo;  
int pos = 75;

QTRSensorsAnalog qtra((unsigned char[]) {0, 1, 2, 3}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
int MOTOR1_PIN1 = 3;
int MOTOR1_PIN2 = 5;
int MOTOR2_PIN1 = 6;
int MOTOR2_PIN2 = 9;
int DEFAULT_WHITE = 100; 
int DEFAULT_BLACK = 500; 



void setup()
{
  delay(500);
  myservo.attach(9);  
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



  
  delay(1000);
}

void loop()
{
qtra.read(sensorValues);
int volts = analogRead(4);
if (volts < 300)
  { if (pos<150)
    {pos = pos +1;                              
    myservo.write(pos);              
    delay(15);     } 
    
    if (sensorValues[0] < 100 && sensorValues[3]< 100 && sensorValues[1] >500 || sensorValues[2]>500 )
    go (50,50);
   
  
     if (sensorValues[0] >500 && sensorValues[3]<100 && volts<400 )
    go(100, -100);
   
        if (sensorValues[0] <100 && sensorValues[3]> 500 && volts<400 )
         go(-100,100);
         
  if (sensorValues[0]>500 && sensorValues[1] >500 && sensorValues[2] >500 && sensorValues[3]<100 )
         
        go (100,-100);
        if (sensorValues[0]<100 && sensorValues[1] >500 && sensorValues[2] >500 && sensorValues[3]>500 )
         
        go(-100,100);
    if (sensorValues[0]<100 && sensorValues[1] <100 && sensorValues[2] <100 && sensorValues[3]<100 )
         go (-75,-75); }
        else go(0,0);
        
          
   
  unsigned int position = qtra.readLine(sensorValues);
  
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


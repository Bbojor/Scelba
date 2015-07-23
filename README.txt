								InfoEducatie 2015 - Etapa Nationala
                                                                             -Scelba-			


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


---------------------------------------------------------

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


----------------------------------------------------------

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




Surse :   http://www.robofun.ro

          https://github.com/pololu/qtr-sensors-arduino
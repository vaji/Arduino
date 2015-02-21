#include <ADXL345.h>
#include <bma180.h>
#include <HMC58X3.h>
#include <ITG3200.h>
#include <MS561101BA.h>
#include <I2Cdev.h>
#include <MPU60X0.h>
#include <EEPROM.h>

#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <Wire.h>
#include <SPI.h>

float angles[3];
float new_angle;
float old_angle = 0;
float delta_x;

const int angle_error = 0.15;
const int minimal_power = 130;
FreeIMU GYRO =  FreeIMU();

byte work_power = 0;
boolean motors_module_on = true;
const int motors_power_pin = A0;
const int motors_b_1 = 3;
const int motors_b_2 = 5;
const int motors_a_1 = 6;
const int motors_a_2 = 9;

const int prox_echo = A2;
const int prox_trig = A3;
void setup() {
  
    Wire.begin();
    Serial.begin(9600);
    
    delay(5);
    GYRO.init();
    delay(5);
    
    pinMode(motors_power_pin,OUTPUT);
    //pinMode(motors_b_1,OUTPUT);
  //  pinMode(motors_b_2,OUTPUT);
   // pinMode(motors_a_1,OUTPUT);
   // pinMode(motors_a_2,OUTPUT);
    
   pinMode(prox_trig,OUTPUT);
   pinMode(prox_echo,INPUT);
}

void loop()
{

   digitalWrite(motors_power_pin,HIGH);
  

  
  
  
 /*  long duration, distance;
  digitalWrite(prox_trig,LOW);
  delayMicroseconds(2);
  digitalWrite(prox_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(prox_trig,LOW);
  duration = pulseIn(prox_echo,HIGH);
  distance = (duration/2) / 29.1;
  */
 // Serial.println(distance);
  
  // if(distance < 100) motors_module_on = false;
 //  else motors_module_on = true;
 

  GYRO.getYawPitchRoll(angles);
 
  //Serial.println(angles[1]);
  new_angle = angles[1];
  delta_x = new_angle - old_angle;
  Serial.println(delta_x); 
//  Serial.println(work_power);
  //forward();

     if(abs(angles[1]) > 0.5)
    {
     // work_power = map(angles[1], 0,-90,255,0);
      //if(work_power > minimal_power) work_power = minimal_power;
      //if(angles[1] < -5) work_power = 0;
     // else work_power = minimal_power;
       if(abs(angles[1]) > 3) work_power = 0;
       else work_power = ((1/8) / abs(angles[1])) - 0.04;   
    }
    else work_power = 255;
    
    if(angles[1] > 0) forward();
    else if (angles[1] < 0) backward();
    else stopp();

   /*
     if(abs(delta_x) > 0.01) {
        if(abs(delta_x) > 0.36) work_power = 0;
      else work_power = -708 * abs(delta_x) + 255;
     
      // work_power = 0;
      backward();
     } else stopp();
     */
 
 
 // else if(angles[1] > -0.3)
//  {
    //int temp_power = angles[1] - 90;
  //  work_power = map(angles[1], 2,90,255,0);
  //  if(work_power > minimal_power) work_power = minimal_power;
  /*  if(abs(delta_x) > 0.01) {
      if(abs(delta_x) > 0.36) work_power = 0;
      else work_power = -708 * abs(delta_x) + 255;
      //work_power = 0;
      forward();
     } else stopp();
  } else
   */


  //Serial.print("AcX = "); Serial.print(AcX);
/// // Serial.print(" | AcY = "); Serial.print(AcY);
/// Serial.print(" | AcZ = "); Serial.print(AcZ);
// Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
//Serial.print(" | GyX = "); Serial.print(GyX);
 //Serial.print(" | GyY = "); Serial.print(GyY);
  //Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(2);
 

  old_angle = new_angle;
}



void forward()
{

  analogWrite(motors_a_1,work_power);
  analogWrite(motors_a_2,255);
  analogWrite(motors_b_1,work_power);
  analogWrite(motors_b_2,255);
}

void backward()
{
  analogWrite(motors_a_1,255);
  analogWrite(motors_a_2,work_power);
  analogWrite(motors_b_1,255);
  analogWrite(motors_b_2,work_power);
}

void turn()
{
  analogWrite(motors_a_1,255);
  analogWrite(motors_a_2,0);
  analogWrite(motors_b_1,0);
  analogWrite(motors_b_2,255);
}

void stopp()
{
   analogWrite(motors_a_1,0);
  analogWrite(motors_a_2,0);
  analogWrite(motors_b_1,0);
  analogWrite(motors_b_2,0);
}

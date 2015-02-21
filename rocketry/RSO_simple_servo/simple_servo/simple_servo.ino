// Simple Servo Control
// by TinkerGuy <http://tinkerguy.eu> 
// This example code is in the public domain.

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
            
void setup() 
{ 
  myservo.attach(14);  // attaches the servo on pin A0 to the servo object 
} 
 
 
void loop() 
{ 
                             
    myservo.write(0); // tell servo to rotate to 0 angle 
                      // remember that servo can rotate from 0 to 180 degrees 
    delay(500);      // wait some time to allow servo reach new angle
    
     int pos = 15;                    
   // myservo.write(pos);   //  you can  pass variables to this method      
                       
   //  myservo.detach(); // this disables servo
} 

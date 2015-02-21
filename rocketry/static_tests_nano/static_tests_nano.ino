#include <VirtualWire.h>

const int led_pin_start = 7;
const int led_pin_ready = 6;

const int relay_pin = 3;
const int pin_in = 9;

int czas_start = 0;
int started = 0;
int delay_timer = 20;
void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin_start, OUTPUT);
  pinMode(led_pin_ready, OUTPUT);
  pinMode(pin_in,INPUT);
  
   Serial.begin(9600);
  

}

void loop() {
  

  // put your main code here, to run repeatedly: 
 
   //receive_data();
  
  if(!started) {
    int buttonS = digitalRead(pin_in);
    if(buttonS)
    {
       digitalWrite(led_pin_start,HIGH);
      czas_start-=1;
    }
    else
    {
       czas_start = 5;
       digitalWrite(led_pin_start,LOW);
    }
    
    if(czas_start < 0)
    { 
      digitalWrite(led_pin_ready,HIGH);
      digitalWrite(led_pin_start,LOW);
      started = 1;
      delay_timer = 20;
    }
  } else
  {
    digitalWrite(led_pin_ready,HIGH);
    delay_timer -= 1;
    if(delay_timer < 0)
    {
      digitalWrite(relay_pin,HIGH);
      delay_timer = 20;
    }
  }
  delay(1000);
 //  receive_data();
}



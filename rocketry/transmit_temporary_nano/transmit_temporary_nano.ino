#include <VirtualWire.h>

const int led_pin = 5;
const int transmit_pin = 12;
const int transmit_on_pin = 3;
const int led_pin_ready = 2;
const int pin_in = 6;

int nadawac = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
  pinMode(led_pin_ready, OUTPUT);
  pinMode(pin_in,INPUT);
  
   Serial.begin(9600);
  vw_set_tx_pin(transmit_pin);
 // vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_on_pin);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  

}

void loop() {
  
  char msg[1] = {'l'};
  // put your main code here, to run repeatedly: 

  nadawac = digitalRead(pin_in);
 
   //receive_data();
   Serial.print(nadawac);
    digitalWrite(led_pin,LOW);
  if(nadawac == 1)
  {
    transmit_data(msg,1);
   // digitalWrite(led_pin,HIGH);
  }
  delay(250);
 //  receive_data();
}

void transmit_data(char msg[], int length)
{
   digitalWrite(led_pin,HIGH);
   vw_send((uint8_t*)msg,length);
   vw_wait_tx();
   digitalWrite(led_pin, LOW);
}

void receive_data()
{
  uint8_t buffer[VW_MAX_MESSAGE_LEN];
  uint8_t buffer_l = VW_MAX_MESSAGE_LEN;
 // Serial.print("elo");
  if(vw_get_message(buffer, &buffer_l))
  {
    int i;
    Serial.print("Received: ");
    for(i = 0;i< buffer_l; i++)
    {
       
       Serial.print((char *)buffer[i]);
       Serial.print(' ');
    }
    Serial.println();
    // dodac diode receivera    
  }  
}

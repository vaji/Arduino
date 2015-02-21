#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_on_pin = 3;


void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
   Serial.begin(9600);
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_on_pin);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  digitalWrite(7,LOW);
  vw_rx_start();
}

void loop() {
  
//  char msg[1] = {'s'};
  // put your main code here, to run repeatedly: 

  //transmit_data(msg,1);
   receive_data();
   //digitalWrite(7,LOW);
 // delay(1000);
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
       
       Serial.print((char)buffer[i]);
       
      
        fire();
        
    }
    Serial.println();
    // dodac diode receivera    
  }  
}

void fire()
{
  Serial.print("fired!");
    digitalWrite(7,HIGH);
}

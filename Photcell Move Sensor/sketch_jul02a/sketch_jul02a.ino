  int pushButton = 2;
const int speed1 = 255;

const int echoPin = 4;
const int trigPin = 3;

const int motor_right_A = 10;
const int motor_right_B = 11;

const int motor_left_A = 13;
const int motor_left_B = 12;

int czas = 0;
long duration, distance;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  
  pinMode(8,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);  
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration /58.1;
  // read the input pin:
 
   digitalWrite(motor_right_A,LOW);
    digitalWrite(motor_right_B,HIGH);
     digitalWrite(motor_left_A,LOW);
      digitalWrite(motor_left_B,HIGH);
  if(distance > 40) {
   // motor_drive(2);
  } else 
  {
    //turn(1);
  }
  Serial.println(distance);
  delay(500);        // delay in between reads for stability
  czas++;
}

void motor_drive(int ile)
{
  // -1 lewy
  // 1 prewy
  // 2 oba
  if(ile == 1)
  {
    motor_stop();
    
    digitalWrite(motor_right_A,HIGH);
    digitalWrite(motor_right_B,LOW);
    
    digitalWrite(motor_left_B,HIGH);
    digitalWrite(motor_left_A,LOW);
    
   }
  if(ile == -1)
  {
    motor_stop();
    digitalWrite(motor_right_A,LOW);
    digitalWrite(motor_right_B,HIGH);
    
    digitalWrite(motor_left_B,LOW);
    digitalWrite(motor_left_A,HIGH);
  }
  if(ile == 2)
  {
    digitalWrite(motor_left_B,LOW);
    digitalWrite(motor_left_A,HIGH);
    
    digitalWrite(motor_right_A,HIGH);
    digitalWrite(motor_right_B,LOW);
  }
  
}

void turn(int side)
{
  if(side == 1) //prawwa
  {
    motor_drive(-1); // krece lewym
  } else if(side == -1)
  {
    motor_drive(1);
  }
 
}
void motor_stop()
{
   digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
}

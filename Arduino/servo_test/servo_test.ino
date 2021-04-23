#include <Servo.h>

Servo myservo; 

int potpin = 0;
int val;    

void setup() {
  myservo.attach(3);
  Serial.begin(9600);
}

void loop() {
  
  myservo.write(110);
  delay(15);         
}

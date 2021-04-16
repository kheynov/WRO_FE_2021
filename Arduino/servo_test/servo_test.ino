#include <Servo.h>

Servo myservo; 

int potpin = 0;
int val;    

void setup() {
  myservo.attach(6);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potpin);
  val = map(val, 0, 1023, 55, 95);
  myservo.write(val);
  Serial.println(val);             
  delay(15);         
}

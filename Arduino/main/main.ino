#include <Wire.h>
#include <Servo.h>
#include "Ultrasonic.h"

#define SLAVE_ADDRESS 0x04

#define SERVO_ADDRESS 0x01
#define MOTOR_ADDRESS 0x02
#define LEFT_SENSOR 0x0A
#define RIGHT_SENSOR 0x0B

#define MIN_SERVO_VALUE 50
#define MAX_SERVO_VALUE 110

#define SERVO_PIN 3
#define SONIC_1_TRIG_PIN 5
#define SONIC_1_ECHO_PIN 6

#define SONIC_2_TRIG_PIN 11
#define SONIC_2_ECHO_PIN 10

#define MOTOR_IN1_PIN 7
#define MOTOR_IN2_PIN 8
#define MOTOR_EN1_PIN 9

Servo servo;
Ultrasonic left_sensor(SONIC_1_TRIG_PIN, SONIC_1_ECHO_PIN);
Ultrasonic right_sensor(SONIC_2_TRIG_PIN, SONIC_2_ECHO_PIN);

int servoPosition = ((MAX_SERVO_VALUE - MIN_SERVO_VALUE) / 2) + MIN_SERVO_VALUE;
int motorPower = 0;

byte controlByte = 0;
byte valueByte = 0;
byte responseByte = 0;

void setup()
{
	servo.attach(SERVO_PIN);
	servo.write(servoPosition);

	pinMode(MOTOR_IN1_PIN, OUTPUT);
	pinMode(MOTOR_IN2_PIN, OUTPUT);
	pinMode(MOTOR_EN1_PIN, OUTPUT);

	Serial.begin(9600);
	Wire.begin(SLAVE_ADDRESS);
	Wire.onReceive(receiveData);
	Wire.onRequest(sendData);
}

void loop()
{
	delay(100);
	servo.write(servoPosition);
	set_motor_power(motorPower);
}

void receiveData(int byteCount)
{
	while (Wire.available())
	{
		if (controlByte == 0)
		{
			controlByte = Wire.read();
		}
		else
		{
			valueByte = Wire.read();

			switch (controlByte)
			{
			case SERVO_ADDRESS:
				Serial.print("Setting servo angle to: ");
				Serial.println(valueByte);
				servoPosition = map(valueByte, 0, 90, MIN_SERVO_VALUE, MAX_SERVO_VALUE);
				responseByte = 0;
				break;
			case MOTOR_ADDRESS:
				Serial.print("Setting main motor power to: ");
				Serial.println(valueByte);
				motorPower = valueByte;
				//				set_motor_power(valueByte);
				responseByte = 0;
				break;
			case LEFT_SENSOR:
				Serial.println("Sending left sensor value");
				responseByte = measure_dist(LEFT_SENSOR);
				break;
			case RIGHT_SENSOR:
				Serial.println("Sending right sensor value");
				responseByte = measure_dist(RIGHT_SENSOR);
				break;
			}
			controlByte = 0;
			valueByte = 0;
		}
	}
}

float measure_dist(int port)
{
	if (port == LEFT_SENSOR)
	{
		return left_sensor.Ranging(CM);
	}
	else if (port == RIGHT_SENSOR)
	{
		return right_sensor.Ranging(CM);
	}
}

void set_motor_power(int power)
{
	char direction;
	if (power >= 0) direction = 1;
	else {
		direction = -1;
		power *= direction;
	}

	power = map(power, 0, 100, 0, 255);
	Serial.println(String(direction) + " # " + String(power));
	if (power == 0)
	{
		digitalWrite(MOTOR_IN1_PIN, LOW);
		digitalWrite(MOTOR_IN2_PIN, LOW);
		digitalWrite(MOTOR_EN1_PIN, LOW); // analog pin umer
	}
	else
	{
		if (direction == 1) {
			digitalWrite(MOTOR_IN1_PIN, LOW);
			digitalWrite(MOTOR_IN2_PIN, HIGH);
		} else {
			digitalWrite(MOTOR_IN1_PIN, HIGH);
			digitalWrite(MOTOR_IN2_PIN, LOW);
		}
		digitalWrite(MOTOR_EN1_PIN, HIGH); // analog pin umer
	}
}

void sendData()
{
	Wire.write(responseByte);
}

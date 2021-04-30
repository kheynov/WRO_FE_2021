#define MOTOR_IN1_PIN 7
#define MOTOR_IN2_PIN 8
#define MOTOR_EN1_PIN 9
#define pot_pin A0

void setup()
{
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);
    pinMode(MOTOR_EN1_PIN, OUTPUT);
    pinMode(pot_pin, INPUT);
}
void loop()
{
    int val = 200;
    if (val <= 20)
    {
        digitalWrite(MOTOR_IN1_PIN, HIGH);
        digitalWrite(MOTOR_IN2_PIN, HIGH);
        digitalWrite(MOTOR_EN1_PIN, LOW);
    }else{
        digitalWrite(MOTOR_IN1_PIN, HIGH);
        digitalWrite(MOTOR_IN2_PIN, LOW);
        analogWrite(MOTOR_EN1_PIN, val);
    }
    
}

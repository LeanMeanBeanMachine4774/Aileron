#include <Arduino.h>
#include <Servo.h>

#define ANGLE_TOLERANCE 2
#define SERVO1_PIN 10
#define ZERO_OFFSET 90
#define BUTTON_PIN 9
#define MINIMUM_SERVO_TRAVEL -30
#define MAXIMUM_SERVO_TRAVEL 30
#define POT1_PIN A0

Servo servo1;

int servo_angle = ZERO_OFFSET;

void setup() {
  servo1.attach(SERVO1_PIN);
  Serial.begin(9600);
}

void loop() {
  servo1.write(servo_angle + ZERO_OFFSET);
  int desired_angle = map(analogRead(POT1_PIN), 0, 1023, MINIMUM_SERVO_TRAVEL, MAXIMUM_SERVO_TRAVEL);
  Serial.println(desired_angle);
  if (abs(servo_angle - desired_angle) > ANGLE_TOLERANCE){
     servo_angle = desired_angle;
  }
}
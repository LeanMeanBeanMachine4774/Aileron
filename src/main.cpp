#include <Arduino.h>
#include <Servo.h>

#define ANGLE_TOLERANCE 1
#define SERVO1_PIN 10
#define ZERO_OFFSET 90
#define BUTTON_PIN 9
//Servo travel from onshape assembly (https://cad.onshape.com/documents/d18afc04477c0a37ba3a6c4c/w/296bb2347621a61e29efeed9/e/c0daab103472e3648c63e07d?renderMode=0&uiState=67d52d3223160a63ec30cd7a)
#define MAXIMUM_ELEVATION 30
#define MAXIMUM_DEPRESSION -55
#define POT1_PIN A0

Servo servo1;

int servo_angle = 0;
bool neutral_mode = true;


void setup() {
  servo1.attach(SERVO1_PIN);
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  bool button = digitalRead(BUTTON_PIN);
  servo1.write(servo_angle + ZERO_OFFSET);
  if (neutral_mode){
    servo_angle = 0;
    if (!button){
      neutral_mode = false;
    }
  }
  if (!neutral_mode){
    int desired_angle = map(analogRead(POT1_PIN), 0, 1023, MAXIMUM_DEPRESSION, MAXIMUM_ELEVATION);
    Serial.println(desired_angle);
    if (abs(servo_angle - desired_angle) > ANGLE_TOLERANCE){
      servo_angle = desired_angle;
    }
  }
  
}
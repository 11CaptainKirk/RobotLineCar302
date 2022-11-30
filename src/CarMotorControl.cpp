#include "Arduino.h"


const int AIN1 = 13;
const int AIN2 = 12;
const int PWMA = 11;

const int BIN1 = 8;
const int BIN2 = 9;
const int PWMB = 10;


int switchPin = 7;
int motorSpeed = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin, INPUT_PULLUP);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);

  Serial.println("Enter motor speed (0-255)... ");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    motorSpeed = Serial.parseInt();
    Serial.println(abs(-1234));
    Serial.print("Motor Speed: ");
    Serial.println(motorSpeed);
  }

  if (digitalRead(7) == LOW) {
    spinMotor(motorSpeed);
  }
  else {
    spinMotor(0);
  }


}

void spinMotor(int motorSpeed) {
  if (motorSpeed > 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  else if (motorSpeed < 0) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }
  else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
  analogWrite(PWMA, abs(motorSpeed));
  analogWrite(PWMB, abs(motorSpeed));
}

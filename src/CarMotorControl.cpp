
#include "Arduino.h"

const int AIN1 = 13;
const int AIN2 = 12;
const int BIN2 = 9;
const int BIN1 = 8;
const int PWMA = 11;
const int PWMB = 10; // the second motor added


int switchPin = 7;


typedef enum TURN_DIRECTION {
  LEFT,
  RIGHT,
};


void spinMotor(int motorSpeed, uint8_t motor) {

  if (motor == PWMA) {
    if (motorSpeed > 0) {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);

    }
    else if (motorSpeed < 0) {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
    }
    else if (motorSpeed == 0) {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
    }
  }
  else if (motor == PWMB) {
    if (motorSpeed > 0) {
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    }
    else if (motorSpeed < 0) {
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
    }
    else if (motorSpeed == 0) {
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
    }
  }
  analogWrite(motor, motorSpeed);
}

void speed(int moveSpeed) {
  spinMotor(moveSpeed, PWMA);
  spinMotor(moveSpeed, PWMB);
}

void turn(TURN_DIRECTION direction, uint8_t turnSpeed) {
  if (direction == LEFT) {
    spinMotor(turnSpeed, PWMA);
    spinMotor(-turnSpeed, PWMB);
  }
  else {
    spinMotor(-turnSpeed, PWMA);
    spinMotor(turnSpeed, PWMB);
  }
}





void setup() {
  pinMode(switchPin, INPUT_PULLUP);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);

  speed(200);
  delay(1000);
  speed(int(-200));
  delay(1000);
  speed(0);
  /*turn(LEFT, 200);
  delay(1000);
  turn(RIGHT, 200);
  delay(1000);
  speed(0);*/
}

void loop() {


}


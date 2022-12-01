
#include "Arduino.h"
#include "basicDrive.h"
#include "navigation.h"





void drive() {
  MOVE_NEEDED move = moveNeeded();
  p("move: " + encodeDirection(move));
  switch (move) {
  case STRAIGHT:
    speed(100);
    break;
  case SMALL_LEFT:
    turn(LEFT, 150);
    break;
  case SMALL_RIGHT:
    turn(RIGHT, 150);
    break;
  case BREAK_LEFT:
    driveForwardToPivot();
    while (moveNeeded() != STRAIGHT) {
      turn(LEFT, 100);
      delay(50);
    }
    break;
  case BREAK_RIGHT:
    driveForwardToPivot();
    while (moveNeeded() != STRAIGHT) {
      turn(RIGHT, 100);
      delay(50);
    }
    break;
  case FAST:
    speed(200);
    break;
  case STOP:
    speed(0);
    break;
  }
}


void setup() {

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);



}


bool driveYes = true;

void loop() {

  if (driveYes) {
    drive();
    delay(75);
  }
  else {
    speed(0);
  }
}


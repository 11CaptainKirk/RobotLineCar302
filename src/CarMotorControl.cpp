
#include "Arduino.h"
#include "basicDrive.h"






/*
    black: 723-844
    red: 490-692
    white: 158-594
*/



enum COLOR {
  WHITE,
  BLACK,
  RED
};

COLOR lineStatus(uint8_t lineSensor) {
  int value = analogRead(lineSensor);
  //p(value);
  if (value < WHITE_MAX) {
    return WHITE;
  }
  else if (value > WHITE_MAX && value < BLACK_MIN) {
    return RED;
  }
  else {
    return BLACK;
  }
}


enum MOVE_NEEDED {
  SMALL_LEFT, //0
  SMALL_RIGHT, //1
  BREAK_LEFT, //2
  BREAK_RIGHT, //3
  STRAIGHT, //4
  FAST,//5
  STOP//6
};

String encodeDirection(MOVE_NEEDED direction) {
  switch (direction) {
  case SMALL_LEFT:
    return "SMALL_LEFT";
  case SMALL_RIGHT:
    return "SMALL_RIGHT";
  case BREAK_LEFT:
    return "BREAK_LEFT";
  case BREAK_RIGHT:
    return "BREAK_RIGHT";
  case STRAIGHT:
    return "STRAIGHT";
  case FAST:
    return "FAST";
  case STOP:
    return "STOP";
  default:
    return "NONE";
  }

}




MOVE_NEEDED moveNeeded() {
  COLOR left = lineStatus(LINE_LEFT);
  COLOR mid = lineStatus(LINE_MID);
  COLOR right = lineStatus(LINE_RIGHT);
  p("L: " + String(left) + " M: " + String(mid) + " R: " + String(right));

  if (left == WHITE && mid == BLACK && right == WHITE) {
    return STRAIGHT;
  }
  else if (left == WHITE && mid == WHITE && right == BLACK) {
    return SMALL_RIGHT;
  }
  else if (left == WHITE && mid == BLACK && right == BLACK) {
    return BREAK_RIGHT;
  }
  else if (left == BLACK && mid == WHITE && right == WHITE) {
    return SMALL_LEFT;
  }
  else if (left == BLACK && mid == BLACK && right == WHITE) {
    return BREAK_LEFT;
  }
  else if (left == BLACK && mid == BLACK && right == BLACK) {
    return FAST;
  }
  else if (left == RED && mid == RED && right == RED) {
    return STOP;
  }
  /*else if (left == WHITE && mid == WHITE && right == WHITE) {
    return STRAIGHT;
  }*/
  else {
    return STOP;
  }
}

void driveForwardToPivot() {
  speed(100);
  delay(MS_TO_PIVOT);
  speed(0);
}

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


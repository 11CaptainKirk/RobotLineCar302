
#include "Arduino.h"

const int AIN1 = 13;
const int AIN2 = 12;
const int BIN2 = 9;
const int BIN1 = 8;
const int PWMA = 11;
const int PWMB = 10; // the second motor added


const int lineLeft = A0;// the line sensors
const int lineMid = A1;
const int lineRight = A2;

#define WHITE_MAX 750
#define BLACK_MIN 750

#define MS_TO_PIVOT 200 // the number of MS to drive before we reach the pivot point at 100 speed




/*
black min 723
844

red min 490
692

white min 158
594
*/



int switchPin = 7;


typedef enum TURN_DIRECTION {
  LEFT,
  RIGHT,
};


void spinMotor(int motorSpeed, int motor) {

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
  analogWrite(motor, abs(motorSpeed));
}

void speed(int moveSpeed) {
  spinMotor(moveSpeed * 1, PWMA);
  spinMotor(moveSpeed, PWMB);
}

void turn(TURN_DIRECTION direction, uint8_t turnSpeed) {
  if (direction == LEFT) {
    spinMotor(-turnSpeed, PWMA);
    spinMotor(turnSpeed, PWMB);
  }
  else {
    spinMotor(turnSpeed, PWMA);
    spinMotor(-turnSpeed, PWMB);
  }
}



typedef enum COLOR {
  WHITE,
  BLACK,
  RED
};

COLOR lineStatus(uint8_t lineSensor) {
  int value = analogRead(lineSensor);
  //Serial.println(value);
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


typedef enum MOVE_NEEDED {
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
  }
}




MOVE_NEEDED moveNeeded() {
  COLOR left = lineStatus(lineLeft);
  COLOR mid = lineStatus(lineMid);
  COLOR right = lineStatus(lineRight);
  Serial.println("L: " + String(left) + " M: " + String(mid) + " R: " + String(right));

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
  Serial.println("move: " + encodeDirection(move));
  switch (move) {
  case STRAIGHT:
    speed(175);
    break;
  case SMALL_LEFT:
    turn(LEFT, 200);
    break;
  case SMALL_RIGHT:
    turn(RIGHT, 200);
    break;
  case BREAK_LEFT:
    driveForwardToPivot();
    turn(LEFT, 255);
    delay(100);
    break;
  case BREAK_RIGHT:
    driveForwardToPivot();
    turn(RIGHT, 255);
    delay(100);
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
  pinMode(switchPin, INPUT_PULLUP);

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


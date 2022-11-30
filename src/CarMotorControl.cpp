
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

#define WHITE_MAX 500
#define BLACK_MIN 700



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


typedef enum COLOR {
  RED,
  BLACK,
  WHITE
};

COLOR lineStatus(uint8_t lineSensor) {
  int value = analogRead(lineSensor);
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
  SMALL_LEFT,
  SMALL_RIGHT,
  BREAK_LEFT,
  BREAK_RIGHT,
  STRAIGHT,
  FAST,
  STOP
};


MOVE_NEEDED moveNeeded() {
  COLOR left = lineStatus(lineLeft);
  COLOR mid = lineStatus(lineMid);
  COLOR right = lineStatus(lineRight);
  Serial.println("left: " + String(left) + " mid: " + String(mid) + " right: " + String(right));

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
  else {
    return STOP;
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



  speed(-200);
  delay(1000);
  speed(-200);
  delay(1000);
  speed(0);

  turn(LEFT, 200);
  delay(1000);
  turn(RIGHT, 200);
  delay(1000);
  speed(0);
}




void loop() {


}


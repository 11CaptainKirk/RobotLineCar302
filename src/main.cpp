
#include "Arduino.h"
#include "basicDrive.h"
//#include "navigation.h"
#include "driveLogic.hh"


void setup() {

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(ENABLE_SWITCH, INPUT_PULLUP);

  Serial.begin(9600);
  delay(2000);
}

#define SHOULD_DRIVE true

uint8_t turnsToTake[] = { 0 };


void loop() {

#if SHOULD_DRIVE
  drive(turnsToTake);
  // function to figure out where we are
  // Detect obstacles function
  delay(30);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
#else
  turn(RIGHT, 255);
  delay(1000);
  turn(LEFT, 255);
  delay(1000);
  speed(255);
  delay(1000);
  speed(-255);
  delay(1000);
  /*
    turn(LEFT, 255);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(150);
    turn(RIGHT, 255);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(60);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  */
#endif
}


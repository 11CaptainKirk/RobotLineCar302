
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

  Serial.begin(9600);

}

#define SHOULD_DRIVE true

uint8_t turnsToTake[] = { 1,2,4 };
uint8_t* turnsToTakePtr = turnsToTake;


void loop() {

#if SHOULD_DRIVE
  drive(&turnsToTakePtr);
  // Detect obstacles function
  delay(75);
#else
  speed(0);
#endif
}


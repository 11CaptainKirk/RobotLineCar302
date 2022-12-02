#ifndef BASIC_DRIVE
#define BASIC_DRIVE


#include "Arduino.h"
#include "globalDefines.h"






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


void driveForwardToPivot() {
    speed(170);
    pl("DRIVING FORWARD TO PIVOT");
    delay(MS_TO_PIVOT);
    pl("DONE DRIVING FORWARD TO PIVOT");
    speed(0);
    delay(500);
}

#endif
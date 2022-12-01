
#include "Arduino.h"
#include "globalDefines.h"
#include "navigation.h"
#include "basicDrive.h"



void drive() {
    MOVE_NEEDED move = moveNeeded();
    pl("move: " + encodeDirection(move));
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
    case LOST:
        while (moveNeeded() != STRAIGHT) {
            turn(RIGHT, 100);
            delay(50);
        } // TODO : Maybe reimplement this to be better
        break;
    case STOP:
        speed(0);
        break;
    }
}


#include "Arduino.h"
#include "globalDefines.h"
#include "navigation.h"
#include "basicDrive.h"


int lastTurnTime = 0;






void drive(uint8_t turnsToTake[]) {
    MOVE_NEEDED move = moveNeeded();
    lastMove = move;
    static uint8_t turnIndex = 0; // Static variable initializes to 0 on first call
    static bool hasReachedHighway = false;
    pl("move: " + encodeDirection(move));
    switch (move) {
    case STRAIGHT:
        speed(170);
        digitalWrite(2, HIGH);
        delay(STRAIGHT_CONST);
        break;
    case SMALL_LEFT:
        turn(LEFT, 150);
        digitalWrite(4, HIGH);
        delay(SM_TURN_CONST);
        lastTurnTime = millis();
        break;
    case SMALL_RIGHT:
        turn(RIGHT, 150);
        digitalWrite(5, HIGH);
        delay(SM_TURN_CONST);
        lastTurnTime = millis();
        break;
    case BIG_LEFT:
        turn(LEFT, 180);
        digitalWrite(4, HIGH);
        delay(LG_TURN_CONST);
        lastTurnTime = millis();
        break;
    case BIG_RIGHT:
        turn(RIGHT, 180);
        digitalWrite(5, HIGH);
        delay(LG_TURN_CONST);
        lastTurnTime = millis();
        break;
    case U_TURN:
        turn(LEFT, 255);
        delay(1000);
        speed(0);
        lastTurnTime = millis();
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        break;
    case FAST:
        if (millis() - lastTurnTime < 1000) {
            move = STRAIGHT;
            break;
        }
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        speed(220);
        hasReachedHighway = true;
        break;

    case LOST:
        digitalWrite(3, HIGH);
        int num = 1;
        while (move == LOST) {
            pl("WE ARE LOST");
            long prevMillis = millis();

            turn(LEFT, 180);
            for (int i = 0; i < 30; i++) {
                move = moveNeeded();
                if (move != LOST) {
                    break;
                }
                pl("DELAY IS         " + String(20 * num));
                delay(20 * num);
            }
            if (move != LOST) {
                break;
            }
            turn(RIGHT, 180);
            for (int i = 0; i < 30; i++) {
                move = moveNeeded();
                if (move != LOST) {
                    break;
                }
                pl("DELAY IS         " + String(20 * num));
                delay(20 * num);
            }
            num++;
        } // TODO : Maybe reimplement this to be better
        break;
    case STOP:
        speed(0);
        break;
    }
}

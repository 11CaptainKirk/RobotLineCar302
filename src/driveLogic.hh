
#include "Arduino.h"
#include "globalDefines.h"
#include "navigation.h"
#include "basicDrive.h"

/*bool shouldTakeTurn(uint8_t turnsToTake[], uint8_t currTurnIdx) {
    static bool ignoreTurn = false; // bool to hold whether the turn should be ignored. Ignore every other turn: every other time the turn should be taken
    for (uint8_t i = 0; i < sizeof(turnsToTake); i++) {
        if (turnsToTake[i] == currTurnIdx) {
            ignoreTurn = !ignoreTurn; // if false it should not ignore, it returns true
            pl("Should take turn: " + String(ignoreTurn ? "TRUE" : "FALSE"));
            return ignoreTurn;
        }
    }
    return true; // TODO HARD CODED
}*/
bool shouldTakeTurn(uint8_t turnsToTake[], uint8_t currTurnIdx) {
    return true;
}

int lastTurnTime = 0;

void drive(uint8_t turnsToTake[]) {
    MOVE_NEEDED move = moveNeeded();
    lastMove = move;
    static uint8_t turnIndex = 0; // Static variable initializes to 0 on first call
    static bool hasReachedHighway = false;
    pl("move: " + encodeDirection(move));
    switch (move) {
    case STRAIGHT:
        speed(200);
        delay(40);
        digitalWrite(2, HIGH);
        break;
    case SMALL_LEFT:
        turn(LEFT, 180);
        lastTurnTime = millis();
        digitalWrite(4, HIGH);
        break;
    case SMALL_RIGHT:
        turn(RIGHT, 180);
        lastTurnTime = millis();
        digitalWrite(5, HIGH);
        break;
    case BREAK_LEFT:
        move = SMALL_LEFT;
        break;
        digitalWrite(4, HIGH);
        pl("Break left*****" + String(turnIndex));
        pl("WE TAKIN THE TURN");
        lastTurn = LEFT;
        speed(0);
        delay(50);
        if (moveNeeded() != BREAK_LEFT) {
            pl("move: " + encodeDirection(move) + ", last Move: " + encodeDirection(lastMove) + ",    move needed: " + encodeDirection(moveNeeded()) + ".BROKW BECAUDE NO GOOD");
            move = moveNeeded();
            break;
        }
        driveForwardToPivot(); // blocking
        while (moveNeeded() != STRAIGHT) { // block here

            turn(LEFT, 160);
            pl("turning left");
            delay(100);
        }

        break;
    case BREAK_RIGHT:
        move = SMALL_RIGHT;
        break;
        digitalWrite(5, HIGH);
        pl("Break right*****" + String(turnIndex));
        pl("WE TAKIN THE TURN");
        lastTurn = RIGHT;
        speed(0);
        delay(50);
        if (moveNeeded() != BREAK_RIGHT) {
            pl("move: " + encodeDirection(move) + ", last Move: " + encodeDirection(lastMove) + ",    move needed: " + encodeDirection(moveNeeded()) + ".BROKW BECAUDE NO GOOD");
            move = moveNeeded();
            break;
        }
        driveForwardToPivot(); // blocking
        while (moveNeeded() != STRAIGHT) { // block here

            turn(RIGHT, 180);
            p("turning right");
            delay(100);
        }
        break;

    case FAST:
        if (millis() - lastTurnTime < 1000) {
            move = STRAIGHT;
            break;
        }
        digitalWrite(2, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        speed(140);
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
                delay(10 * num);
            }
            turn(RIGHT, 180);
            for (int i = 0; i < 30; i++) {
                move = moveNeeded();
                if (move != LOST) {
                    break;
                }
                delay(10 * num);
            }
            num++;
        } // TODO : Maybe reimplement this to be better
        break;
    case STOP:
        speed(0);
        break;
    }
}

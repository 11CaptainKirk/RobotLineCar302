#ifndef NAV
#define NAV


#include "Arduino.h"
#include "globalDefines.h"



/*
    black: 723-844
    red: 490-692
    white: 158-594
*/

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

String encodeLastMove(MOVE_NEEDED lastMove) {
    switch (lastMove) {
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
    case LOST:
        return "LOST";
    case STOP:
        return "STOP";
    case NO_MOVE:
        return "NO_MOVE";
    default:
        return "ERROR";
    }
}



MOVE_NEEDED moveNeeded() {
    COLOR left = lineStatus(LINE_LEFT);
    COLOR mid = lineStatus(LINE_MID);
    COLOR right = lineStatus(LINE_RIGHT);
    static long lastBreak = millis();
    pl("L: " + String(left) + " M: " + String(mid) + " R: " + String(right));

    if (left == WHITE && mid == BLACK && right == WHITE) {
        return STRAIGHT;
    }
    else if (left == WHITE && mid == WHITE && right == BLACK) {
        return SMALL_RIGHT;
    }
    else if (left == WHITE && mid == BLACK && right == BLACK) {
        pl(" .                     LAST MOVE:" + encodeLastMove(lastMove));
        pl(" .                     time:" + String(millis() - lastBreak));
        if (millis() - lastBreak > 2000) {
            lastBreak = millis();
            return BREAK_RIGHT;
        }
        else {
            return  SMALL_RIGHT;//BREAK_RIGHT; // * used to be small right
        }

    }
    else if (left == BLACK && mid == WHITE && right == WHITE) {
        return SMALL_LEFT;
    }
    else if (left == BLACK && mid == BLACK && right == WHITE) {
        pl(" .                     LAST MOVE:" + String(lastMove));
        pl(" .                     time:" + String(millis() - lastBreak));
        if (millis() - lastBreak > 2000) {
            lastBreak = millis();
            return BREAK_LEFT;

        }
        else {
            return SMALL_LEFT;// BREAK_LEFT; // * used to be small left
        }
    }
    else if (left == BLACK && mid == BLACK && right == BLACK) {
        return FAST;
    }
    else if (left == RED && mid == RED && right == RED) {
        return STOP;
    }
    else if (left == WHITE && mid == WHITE && right == WHITE) {
        return LOST;
    }
    else if (left == BLACK && mid == WHITE && right == BLACK) {
        return STRAIGHT;
    }
    else {
        return STOP; // Perhaps this should be something to find a valid value like "LOST"
    }
}

#endif
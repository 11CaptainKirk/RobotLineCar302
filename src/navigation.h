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
    else if (left == WHITE && mid == WHITE && right == WHITE) {
        return LOST;
    }
    else {
        return STOP;
    }
}

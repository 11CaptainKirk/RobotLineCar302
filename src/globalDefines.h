#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

#define AIN1 13
#define AIN2 12
#define PWMA 11

#define PWMB 10
#define BIN2 9
#define BIN1 8

#define LINE_LEFT A0
#define LINE_MID A1
#define LINE_RIGHT A2

#define ENABLE_SWITCH 7

#define WHITE_MAX 750
#define BLACK_MIN 751

#define MS_TO_PIVOT 650 // the number of MS to drive before we reach the pivot point at 100 speed

#define PRINTS true

#if PRINTS == true
#define p(x) Serial.print(x)
#define pl(x) Serial.println(x)
#else
#define p(x)
#define pl(x)
#endif




// ENUMS

enum COLOR {
    WHITE,
    BLACK,
    RED
};



enum TURN_DIRECTION {
    LEFT,
    RIGHT,
    NONE
};

enum MOVE_NEEDED {
    SMALL_LEFT, //0
    SMALL_RIGHT, //1
    BREAK_LEFT, //2
    BREAK_RIGHT, //3
    STRAIGHT, //4
    FAST,//5
    LOST,
    STOP,//6
    NO_MOVE
};

// Global Vars
TURN_DIRECTION lastTurn = NONE;
MOVE_NEEDED lastMove = NO_MOVE;




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
    case LOST:
        return "LOST";
    case STOP:
        return "STOP";
    default:
        return "NONE";
    }

}


#endif
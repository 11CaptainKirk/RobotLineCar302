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

#define WHITE_MAX 750
#define BLACK_MIN 750

#define MS_TO_PIVOT 200 // the number of MS to drive before we reach the pivot point at 100 speed

#define PRINTS true

#if PRINTS == true
#define p(x) Serial.print(x)
#define pl(x) Serial.println(x)
#else
#define p(x)
#define pl(x)
#endif

#endif
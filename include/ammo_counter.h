#ifndef AMMO_COUNTER_H
#define AMMO_COUNTER_H

#include "headers.h"

 
    /*                        BLUE-RED-WHITE            BLUE-WHITE-YELLOW-BLUE
    4             2            2   1    0                3    4      6     5
    6             1
                  0
    7             3
    5 
    */

extern const int multiplexer_array[7][3];
extern volatile int currentAmmoCount;
extern volatile int currentDigitOne;
extern volatile int currentDigitTwo;


extern const bool LED_DIGIT_0[7];
extern const bool LED_DIGIT_1[7];
extern const bool LED_DIGIT_2[7];
extern const bool LED_DIGIT_3[7];
extern const bool LED_DIGIT_4[7];
extern const bool LED_DIGIT_5[7];
extern const bool LED_DIGIT_6[7];
extern const bool LED_DIGIT_7[7];
extern const bool LED_DIGIT_8[7];
extern const bool LED_DIGIT_9[7];

extern const bool* LED_DIGITS[10];

void setupAmmoCounter();
void ammoCounterTask(void *parameter);
void ammo_refill_loop();
void displayDigit(int number);
void showDigitOnce(int digitPos, int value, int visibleMs);





#endif
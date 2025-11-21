#ifndef AMMO_COUNTER_H
#define AMMO_COUNTER_H

#include "headers.h"
#define MUX_PIN_A 5 
#define MUX_PIN_B 18
#define MUX_PIN_C 19
#define LED_COMMON_PIN 17
 
    /*                        BLUE-RED-WHITE            BLUE-WHITE-YELLOW-BLUE
    4             2            2   1    0                3    4      6     5
    6             1
                  0
    7             3
    5 
    */

extern const int multiplexer_array[7][3];

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
void mux_loop_task(void *parameter);
void displayNumberLoop(int number);



#endif
#ifndef AMMO_COUNTER_H
#define AMMO_COUNTER_H

#include "headers.h"
#define MUX_PIN_A 16
#define MUX_PIN_B 17
#define MUX_PIN_C 18

const int multiplexer_array[8][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
  };

void setupAmmoCounter();
void ammoCounterTask(void *parameter);


#endif
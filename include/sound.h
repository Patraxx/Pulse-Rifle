#ifndef SOUND_H
#define SOUND_H
#include "headers.h"

extern volatile bool soundOn;

void setupSound();
void gun_fire_task(void *parameter);
void gainCycleTest();

#endif // SOUND_H
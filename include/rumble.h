#ifndef RUMBLE_H
#define RUMBLE_H

extern volatile bool rumbleOn;

void setupRumble();
void rumbleTask(void *parameter);
void stopMotors();
void breakMotors();
void runMotors();

#endif // RUMBLE_H
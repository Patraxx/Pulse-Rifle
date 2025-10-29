#ifndef TRIGGER_H
#define TRIGGER_H

#include "headers.h"



// FreeRTOS task to poll the trigger (internal use)
void triggerTask(void *parameter);

// Set by triggerTask when a press is detected (edge-detected). Read from
// other tasks; it's volatile to be safe between tasks.
extern volatile bool triggerPressed;




#endif // TRIGGER_H
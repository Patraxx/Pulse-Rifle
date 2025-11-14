#ifndef HEADERS_H
#define HEADERS_H

#include <Arduino.h>
#include <AudioFileSourcePROGMEM.h>
#include <AudioGeneratorWAV.h>
#include <AudioOutputI2S.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"
#include <pgmspace.h>
#include "trigger.h"
#include "freertos/event_groups.h"
#include "pulse.h"
#include "sound.h"
#include "rumble.h"

#define vibration_pin 27

extern EventGroupHandle_t EventGroupHandle;
#define VIBRATING_BIT BIT0
#define AUDIO_PLAYING_BIT BIT1
#define AUDIO_INTERRUPT_BIT BIT2
#define AUDIO_START_BIT BIT3
#define RUMBLE_START_BIT BIT4
#define INDEX_SIZE 5
extern volatile int current_sample_index;
#endif // HEADERS_H

#define testMode 1


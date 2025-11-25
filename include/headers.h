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
#include "ammo_counter.h"
#include "freertos/semphr.h"



extern EventGroupHandle_t EventGroupHandle;
#define VIBRATING_BIT BIT0
#define AUDIO_PLAYING_BIT BIT1
#define AUDIO_INTERRUPT_BIT BIT2
#define AUDIO_START_BIT BIT3
#define RUMBLE_START_BIT BIT4
#define AMMO_EXPENDED_BIT BIT5
#define AMMO_REFILLED_BIT BIT6
#define INDEX_SIZE 5
extern volatile int current_sample_index;
extern SemaphoreHandle_t ammoCountMutex;
#define testMode 0

#define MUX_PIN_A 5 
#define MUX_PIN_B 18
#define MUX_PIN_C 19
#define LED_COMMON_PIN 17

#define digitPinOne 16
#define digitPinTwo 4
#define triggerPin 14

#define vibration_pin 27
#define blck_pin 26
#define wclk_pin 25
#define data_out_pin 22
#endif // HEADERS_H


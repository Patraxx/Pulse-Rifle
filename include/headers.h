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
#define AMMO_DRAIN_START_BIT BIT5
#define AMMO_DRAIN_STOP_BIT BIT7
#define AMMO_REFILLED_BIT BIT6
#define AMMO_OUT_BIT BIT8
#define INDEX_SIZE 5
extern volatile int current_sample_index;
extern SemaphoreHandle_t ammoCountMutex;
#define testMode 1

#define MUX_PIN_A 5 
#define MUX_PIN_B 18
#define MUX_PIN_C 19
#define LED_COMMON_PIN 17
//#define debugLED 23

#define digitPinOne 4
#define digitPinTwo 16
#define triggerPin 14


#define blck_pin 26 
#define wclk_pin 25
#define data_out_pin 22
#define LED_PIN1 23

#define MOTOR_PIN_1 32
#define MOTOR_PIN_2 33

#define SettingsButton 35 //turn off vibration, turn off sound, figure out other settings i could need. 

//gpio safe list: 4, 5, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33

//gpio used: 5, 14, 16, 17, 18, 19, 21, 22, 25, 26, 27, 32, 33
#endif // HEADERS_H


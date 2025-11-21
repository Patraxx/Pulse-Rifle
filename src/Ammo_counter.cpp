#include "ammo_counter.h"

static const bool ACTIVE_LOW = true; // Set to true if the LED segments are active low
inline int led_state(bool on) {
    return (on ^ ACTIVE_LOW) ? HIGH : LOW;
}

/* Definitions moved from header to a single translation unit to avoid multiple-definition errors */
const int multiplexer_array[7][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0}
};

const bool LED_DIGIT_0[7]= {1,1,1,1,1,0,1};
const bool LED_DIGIT_1[7]= {0,0,1,0,0,1,0};
const bool LED_DIGIT_2[7]= {1,0,1,1,1,0,1};
const bool LED_DIGIT_3[7]= {1,1,0,1,0,1,1};
const bool LED_DIGIT_4[7]= {0,1,1,0,0,1,1};
const bool LED_DIGIT_5[7]= {1,1,0,0,1,1,1};
const bool LED_DIGIT_6[7]= {1,1,0,1,1,1,1};
const bool LED_DIGIT_7[7]= {1,0,1,0,0,1,0};
const bool LED_DIGIT_8[7]= {1,1,1,1,1,1,1};
const bool LED_DIGIT_9[7]= {1,1,1,0,1,1,1};

const bool* LED_DIGITS[10] = {
   LED_DIGIT_0,
   LED_DIGIT_1,
   LED_DIGIT_2,
   LED_DIGIT_3,
   LED_DIGIT_4,
   LED_DIGIT_5,
   LED_DIGIT_6,
   LED_DIGIT_7,
   LED_DIGIT_8,
   LED_DIGIT_9
};

void mux_loop_task(void *parameter) {
    for (;;) {



        for (int i = 0; i < 7; i++) {
            digitalWrite(MUX_PIN_A, multiplexer_array[i][0]);
            digitalWrite(MUX_PIN_B, multiplexer_array[i][1]);
            digitalWrite(MUX_PIN_C, multiplexer_array[i][2]);
            int led_on = LED_DIGITS[0][i]; // Example: display digit '9'
            digitalWrite(LED_COMMON_PIN, led_on ? LOW : HIGH); // Activate common pin (assuming active low)        
            vTaskDelay(1 / portTICK_PERIOD_MS); // Small delay to allow LED to be visible
        }
    }
    vTaskDelete(NULL);
}

void setupAmmoCounter() {
    pinMode(MUX_PIN_A, OUTPUT);
    pinMode(MUX_PIN_B, OUTPUT);
    pinMode(MUX_PIN_C, OUTPUT);
    pinMode(LED_COMMON_PIN, OUTPUT);
    digitalWrite(LED_COMMON_PIN, HIGH); // Turn off common LED pin initially
}
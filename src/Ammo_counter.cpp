#include "ammo_counter.h"

int volatile currentAmmoCount = 0;

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


void setupAmmoCounter() {
    pinMode(MUX_PIN_A, OUTPUT);
    pinMode(MUX_PIN_B, OUTPUT);
    pinMode(MUX_PIN_C, OUTPUT);
    pinMode(LED_COMMON_PIN, OUTPUT);
    digitalWrite(LED_COMMON_PIN, HIGH); // Turn off common LED pin initially
}



void ammoCounterTask(void *parameter) {
    while (true) {

        currentDigitOne = currentAmmoCount % 10;
        currentDigitTwo = currentAmmoCount / 10;
        displayDigit(urrentDigitOne);
        displayDigit(currentDigitTwo);

   

    }

    

        
      
}
void ammo_refill_loop() {

    while (true) {
        if (currentAmmoCount < 99) {
            currentAmmoCount++;
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void displayDigit(int number) {

    for (int digit = 0; digit < 7; digit++) {

        digitalWrite(MUX_PIN_A, multiplexer_array[digit][0]);
        digitalWrite(MUX_PIN_B, multiplexer_array[digit][1]);
        digitalWrite(MUX_PIN_C, multiplexer_array[digit][2]);

        const bool* segments = LED_DIGITS[number];

        

       
    }
    // Turn off common pin after displaying
    digitalWrite(LED_COMMON_PIN, HIGH);
}

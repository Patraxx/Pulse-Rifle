#include "ammo_counter.h"

volatile int currentAmmoCount = 0;
volatile int currentDigitOne = 0;
volatile int currentDigitTwo = 0;
SemaphoreHandle_t ammoCountMutex = NULL;

static int lastKnownAmmoCount = 0;


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
    pinMode(digitPinOne, OUTPUT);
    pinMode(digitPinTwo, OUTPUT);
    pinMode(LED_COMMON_PIN, OUTPUT);
    digitalWrite(LED_COMMON_PIN, HIGH); // Turn off common LED pin initially
    digitalWrite(digitPinOne, HIGH); // Turn off digit one initially
    digitalWrite(digitPinTwo, HIGH); // Turn off digit two initially
}



void ammoCounterTask(void *parameter) {

    while (true) {
        Serial.println ("Ammo Counter Task running. Current Ammo: " + String(currentAmmoCount));

      //  currentDigitOne = currentAmmoCount % 10;
        //currentDigitTwo = currentAmmoCount / 10;
        currentDigitOne = 0;
        displayDigit(currentDigitOne);


    }
    vTaskDelete(NULL);
}
void ammo_refill_loop() {
    Serial.println("Ammo refill loop started");
    Serial.println("Last known ammo count: " + String(lastKnownAmmoCount));

    while (true) {
        if (currentAmmoCount < 99) {
            currentAmmoCount++;
            vTaskDelay(50/ portTICK_PERIOD_MS);
        }
        
        else {
            break;
        }
    }
    if (testMode) {
        currentAmmoCount = 0;
    }
}

void displayDigit(int number) {
     const bool* segments = LED_DIGITS[number];
    for (int seg = 0; seg < 7; seg++) {

        digitalWrite(MUX_PIN_A, multiplexer_array[seg][0]);
        digitalWrite(MUX_PIN_B, multiplexer_array[seg][1]);
        digitalWrite(MUX_PIN_C, multiplexer_array[seg][2]);
        digitalWrite(LED_COMMON_PIN, segments[seg] ? LOW : HIGH); // Activate segment (assuming common anode)
    }
}

int getAmmmoCount(){

    int localAmmo = -1;
    if (xSemaphoreTake(ammoCountMutex,0) == pdTRUE) {
        localAmmo = currentAmmoCount;
        lastKnownAmmoCount = localAmmo;
        xSemaphoreGive(ammoCountMutex);
    }
    else {Serial.println("Failed to take ammoCountMutex in getAmmoCount()");
    }
    return localAmmo;
}


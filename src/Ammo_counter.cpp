#include "ammo_counter.h"

volatile int currentAmmoCount = 0;
volatile int currentDigitOne = 0;
SemaphoreHandle_t ammoCountMutex = NULL;
volatile int currentDigitTwo = 0;

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



// 1 = off (segment off), 0 = on (segment on)
const bool LED_DIGIT_0[7]= {0,0,0,1,0,0,0};  //KLAR  swappade 5 and 3
const bool LED_DIGIT_1[7]= {1,1,0,1,1,0,1};  
const bool LED_DIGIT_2[7]= {0,0,0,0,1,1,0};  //KLAR
const bool LED_DIGIT_3[7]= {0,0,0,0,1,0,1}; // klar
const bool LED_DIGIT_4[7]= {1,1,0,0,0,0,1}; // KLAR
const bool LED_DIGIT_5[7]= {0,0,1,0,0,0,1};  // KLAR, segment 2 och 6 är släckta?
const bool LED_DIGIT_6[7]= {0,0,1,0,0,0,0}; // KLAR
const bool LED_DIGIT_7[7]= {0,1,0,1,1,0,1}; 
const bool LED_DIGIT_8[7]= {0,0,0,0,0,0,0};
const bool LED_DIGIT_9[7]= {0,0,0,0,0,0,1}; //klar







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
/*  backup, no not change!
const bool LED_DIGIT_0[7]= {0,0,0,0,0,1,0};  //KLAR
const bool LED_DIGIT_1[7]= {1,1,0,0,1,1,1};  //KLAR
const bool LED_DIGIT_2[7]= {0,0,0,1,1,0,0};  //KLAR äntligen? 3 och 4 är nu släckta? 
const bool LED_DIGIT_3[7]= {0,0,0,0,1,0,1}; // klar
const bool LED_DIGIT_4[7]= {1,1,0,0,0,0,1}; // KLAR
const bool LED_DIGIT_5[7]= {0,0,1,0,0,0,1};  // KLAR, segment 2 och 6 är släckta?
const bool LED_DIGIT_6[7]= {0,0,1,0,0,0,0}; // KLAR
const bool LED_DIGIT_7[7]= {0,1,0,0,1,1,1};  //KLAR
const bool LED_DIGIT_8[7]= {0,0,0,0,0,0,0};
const bool LED_DIGIT_9[7]= {0,0,0,0,0,0,1};
*/

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



void ammoDrainTask(void *parameter) {
    EventBits_t bits;

    while (true) {
        // Wait until a drain is requested. Do NOT clear the start bit here so
        // other tasks can observe that draining is in progress.
        bits = xEventGroupWaitBits(EventGroupHandle, AMMO_DRAIN_START_BIT, pdFALSE, pdFALSE, portMAX_DELAY);

        // Continue draining until a STOP bit is set elsewhere.
        while (true) {
            bits = xEventGroupGetBits(EventGroupHandle);
            if (bits & AMMO_DRAIN_STOP_BIT) {
                Serial.println("Ammo drain stopped");
                // Clear both START and STOP bits so the state is reset.
                xEventGroupClearBits(EventGroupHandle, AMMO_DRAIN_START_BIT | AMMO_DRAIN_STOP_BIT);
                break;
            }

            if (currentAmmoCount > 0) {
                // consider taking ammoCountMutex here if other tasks modify currentAmmoCount concurrently
                currentAmmoCount--;
            }
            else {
                Serial.println("Ammo depleted");

                if (testMode) {
                    Serial.println("Test mode active: refilling ammo");
                    currentAmmoCount = 30; // refill for testing
                } else {
                    // Signal that ammo is out
                    xEventGroupSetBits(EventGroupHandle, AMMO_OUT_BIT);
                }
                
            }
            vTaskDelay(50 / portTICK_PERIOD_MS); // Drain rat
        }



    }



    vTaskDelete(NULL);
}



void ammoCounterTask(void *parameter) {

    while (true) {
      

      //  currentDigitOne = currentAmmoCount % 10;
        currentDigitTwo = currentAmmoCount / 10;
         currentDigitOne = currentAmmoCount % 10;

            digitalWrite(digitPinOne, LOW); // Activate digit one
            digitalWrite(digitPinTwo, HIGH); // Deactivate digit two   
            displayDigit(currentDigitOne);
            digitalWrite(digitPinOne, HIGH); // Deactivate digit one
            digitalWrite(digitPinTwo, LOW); // Activate digit two
            displayDigit(currentDigitTwo);


        }
    vTaskDelete(NULL);
}
void ammo_refill_loop() {

     currentAmmoCount = 0;
  

    while (true) {
        if (currentAmmoCount < 99) {
            currentAmmoCount++;
            Serial.println(" ammo: " + String(currentAmmoCount));
            vTaskDelay(2000/ portTICK_PERIOD_MS);
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
            if(segments[seg]) {
                digitalWrite(LED_COMMON_PIN, HIGH); // Deactivate segment
            } else {
            digitalWrite(LED_COMMON_PIN, LOW); // Activate segment (assuming common anode)           
        }
        vTaskDelay(1 / portTICK_PERIOD_MS); // Small delay to allow visibility
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


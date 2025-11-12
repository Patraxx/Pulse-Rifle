#include "headers.h"

void setupRumble() {
    pinMode(vibration_pin, OUTPUT);
    digitalWrite(vibration_pin, LOW);
}

void rumbleTask(void *parameter) {
    EventBits_t bits;

        for (;;) {
            bits = xEventGroupWaitBits(EventGroupHandle, RUMBLE_START_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
            Serial.println("Rumble task activated");
            /*
             for(int i = 0; i < 6; i++) {
            bits = xEventGroupGetBits(EventGroupHandle);
            if(bits & AUDIO_INTERRUPT_BIT){
                Serial.println("Rumble interrupted");
                xEventGroupClearBits(EventGroupHandle, RUMBLE_START_BIT);
                break;
            }
            
            digitalWrite(vibration_pin, LOW);
            vTaskDelay(50/ portTICK_PERIOD_MS);
            digitalWrite(vibration_pin, HIGH);
            vTaskDelay(100/ portTICK_PERIOD_MS);
            
        }
            
            
            */
            digitalWrite(vibration_pin, LOW);
            vTaskDelay(400/ portTICK_PERIOD_MS);
            digitalWrite(vibration_pin, HIGH);
            Serial.println("Rumble task finished");
           
     
    }
    vTaskDelete(NULL);
}
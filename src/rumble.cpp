#include "headers.h"



void setupRumble() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(vibration_pin, OUTPUT);
    digitalWrite(vibration_pin, HIGH);
}
void rumbleTask(void *parameter) {
    setupRumble();
   
    EventBits_t bits;

        for (;;) {
            bits = xEventGroupWaitBits(EventGroupHandle, RUMBLE_START_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
            Serial.println("Rumble task activated");

            int max_rumbles = (current_sample_index == 0 || current_sample_index == 1) ? 4 : 8;
          
            for(int i = 0; i < max_rumbles; i++) {
            bits = xEventGroupGetBits(EventGroupHandle);
            if(bits & AUDIO_INTERRUPT_BIT){
                Serial.println("Rumble interrupted");
                xEventGroupClearBits(EventGroupHandle, RUMBLE_START_BIT);
                break;
            }        
            digitalWrite(vibration_pin, LOW);
            digitalWrite(LED_PIN, HIGH);
            currentAmmoCount--;
            vTaskDelay(30/ portTICK_PERIOD_MS);
            digitalWrite(vibration_pin, HIGH);
            digitalWrite(LED_PIN, LOW);
            vTaskDelay(70/ portTICK_PERIOD_MS);       
        }
            
            
           
            
    }
    vTaskDelete(NULL);
}
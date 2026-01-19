#include "headers.h"



void setupRumble() {
    pinMode(MOTOR_PIN_1, OUTPUT);
    pinMode(MOTOR_PIN_2, OUTPUT);

    digitalWrite(MOTOR_PIN_1, LOW);
    digitalWrite(MOTOR_PIN_2, LOW);
}
void stopMotors() {
    digitalWrite(MOTOR_PIN_1, LOW);
    digitalWrite(MOTOR_PIN_2, LOW);
}
void breakMotors() {
    digitalWrite(MOTOR_PIN_1, HIGH);
    digitalWrite(MOTOR_PIN_2, HIGH);
}

void runMotors() {
    digitalWrite(MOTOR_PIN_1, HIGH);
    digitalWrite(MOTOR_PIN_2, LOW);
}

void rumbleTask(void *parameter) {
    pinMode(LED_PIN1, OUTPUT);
    digitalWrite(LED_PIN1, LOW); // Turn off LED initially

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
            digitalWrite(LED_PIN1, HIGH);  //2.6V - 2.4 (efter resistans, 65)
            runMotors();
          
            vTaskDelay(40/ portTICK_PERIOD_MS);
          
              digitalWrite(LED_PIN1, LOW);
            breakMotors();
        
            vTaskDelay(40/ portTICK_PERIOD_MS);       
        }
        stopMotors();
    
                   
           
            
    }
    vTaskDelete(NULL);
}
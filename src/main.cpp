#include "headers.h"
#include "pulse.h"
EventGroupHandle_t EventGroupHandle;

volatile bool automatic_refill_mode = true;
volatile bool soundOn = true;
volatile bool rumbleOn = true;

void setup_adc_buttons() {
    pinMode(SettingsButton, INPUT);
    analogSetAttenuation(ADC_11db); // Set attenuation for full range (0-3.3V)
    analogSetWidth(ADC_WIDTH_12Bit); // Set ADC width to 12 bits
}

void adc_buttons_task(void *parameter) {
    while (true) {

        int adcValue = analogRead(SettingsButton);
        if (adcValue > 500) {
            Serial.println("ADC Value: " + String(adcValue));
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
          
    }
}

void setup() {
 

   setupAmmoCounter();
   setupRumble();

   currentAmmoCount = 99;
  Serial.begin(115200);
  delay(1000); // Give time for Serial to initialize

    
   ammoCountMutex = xSemaphoreCreateMutex();
    EventGroupHandle = xEventGroupCreate();

  

  xTaskCreate(
      ammoDrainTask,          // Task function
      "Ammo Drain Task",       // Name of the task (for debugging)
      2048,                 // Stack size (in words)
      NULL,                 // Task input parameter
      1,                    // Priority of the task
      NULL                  // Task handle
   );
  xTaskCreate(
       ammoCounterTask,          // Task function
      "MUX Loop Task",       // Name of the task (for debugging)
      2048,                 // Stack size (in words)
      NULL,                 // Task input parameter
      1,                    // Priority of the task
      NULL                  // Task handle
   );
  
  xTaskCreate(
      triggerTask,          // Task function
      "Trigger Task",       // Name of the task (for debugging)
      2048,                 // Stack size (in words)
      NULL,                 // Task input parameter
      1,                    // Priority of the task
      NULL                  // Task handle
  );

  xTaskCreate(
      gun_fire_task,          // Task function
      "Gun Fire Task",       // Name of the task (for debugging)
      8192,                 // Stack size (in words)
      NULL,                 // Task input parameter
      1,                    // Priority of the task
      NULL                  // Task handle
  );

  xTaskCreate(
      rumbleTask,          // Task function
      "Rumble Task",       // Name of the task (for debugging)
      2048,                 // Stack size (in words)
      NULL,                 // Task input parameter
      1,                    // Priority of the task
      NULL                  // Task handle
  );
 
  


}



void loop() {


    
  
  





 

   

    
    
}
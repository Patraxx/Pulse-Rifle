#include "headers.h"
#include "pulse.h"
EventGroupHandle_t EventGroupHandle;



void setup() {

   ammoCountMutex = xSemaphoreCreateMutex();

   setupAmmoCounter();
   xTaskCreate(
       ammoCounterTask,          // Task function
      "MUX Loop Task",       // Name of the task (for debugging)
      2048,                 // Stack size (in words)
      NULL,                 // Task input parameter
      1,                    // Priority of the task
      NULL                  // Task handle
   );
  EventGroupHandle = xEventGroupCreate();
 
  pinMode(vibration_pin, OUTPUT);
  digitalWrite(vibration_pin, HIGH);
  Serial.begin(115200);
  delay(1000);
  Serial.println("Start");


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


    if (testMode) {
        currentAmmoCount++;
        digitalWrite(digitPinOne, LOW);
        digitalWrite(digitPinTwo, HIGH);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        currentAmmoCount++;
        digitalWrite(digitPinOne, HIGH);
        digitalWrite(digitPinTwo, LOW);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    
    
}
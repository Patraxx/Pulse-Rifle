#include "headers.h"
#include "pulse.h"
EventGroupHandle_t EventGroupHandle;


void setup() {
  pinMode(debugLED, OUTPUT);
  digitalWrite(debugLED, LOW); // Turn off debug LED initially
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
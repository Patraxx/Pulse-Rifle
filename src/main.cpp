#include "headers.h"
#include "pulse.h"
EventGroupHandle_t EventGroupHandle;


void ammo_test(){
    currentDigitOne = currentAmmoCount % 10;
    currentAmmoCount++;
    digitalWrite(digitPinOne, LOW); // Activate digit one
    digitalWrite(digitPinTwo, HIGH); // Deactivate digit two
    delay(50); // Keep the digit on for 1 second
    currentDigitTwo = currentAmmoCount / 10;
    currentAmmoCount++;
    digitalWrite(digitPinOne, HIGH); // Deactivate digit one
    digitalWrite(digitPinTwo, LOW); // Activate digit two
    delay(50); // Keep the digit on for 1 second
}

void setup() {
   setupAmmoCounter();
   setupRumble();
  Serial.begin(115200);
  delay(1000); // Give time for Serial to initialize

    
   ammoCountMutex = xSemaphoreCreateMutex();
    EventGroupHandle = xEventGroupCreate();

  

  
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

   ammo_refill_loop();

   

    
    
}
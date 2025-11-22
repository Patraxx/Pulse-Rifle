#include "trigger.h"

volatile bool triggerPressed = false;
static int triggerPin = 14; //ändras


static unsigned long lastDebounceTime = 0;
static const unsigned long debounceDelay = 50; // milliseconds


void triggerTask(void *parameter) {
   EventBits_t bits;
  
   //insert auto-fire-mode later
    pinMode(triggerPin, INPUT_PULLUP);

  while (true) {
    int reading = digitalRead(triggerPin);

    static int lastReading = HIGH;
    static bool stableState = HIGH;

    // reset debounce timer on change
    if (reading != lastReading) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      // If the button state has been stable for longer than the debounce delay
      if (reading != stableState) {
        // state changed after debouncing
        stableState = reading;
        if (stableState == LOW) {
          bits = xEventGroupGetBits(EventGroupHandle);
          if ((bits & AUDIO_PLAYING_BIT)) {
            xEventGroupSetBits(EventGroupHandle, AUDIO_INTERRUPT_BIT);
          }

          Serial.println("Trigger pressed!");
          // falling edge detected: button pressed
          xEventGroupSetBits(EventGroupHandle, AUDIO_START_BIT);
          xEventGroupSetBits(EventGroupHandle, RUMBLE_START_BIT);
          xEventGroupSetBits(EventGroupHandle, AMMO_EXPENDED_BIT);
          
        }
      }
    }

    lastReading = reading;
    vTaskDelay(10 / portTICK_PERIOD_MS); // 10 ms
  }
  vTaskDelete(NULL);
}   


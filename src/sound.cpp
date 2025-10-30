#include "headers.h"
#include "sound.h"

AudioGeneratorWAV *wav;

const uint8_t* sample_data[4] = {
normal_pulse,
higher_pulse,
lower_pitched_pulse,
higher_pitched_pulse
};
const size_t sample_lengths[4] = {
    normal_pulse_length,
    higher_pulse_length,
    lower_pitched_length,
    higher_pitched_length
};
AudioOutputI2S *out;




void setupSound() {
   
    wav = new AudioGeneratorWAV();
    out = new AudioOutputI2S();
    out->SetPinout(26, 25, 22);
    out->SetGain(0.8); // 0.0 .. 4.0
}

void gun_fire_task(void *parameter) {
    setupSound();
    EventBits_t bits;

   int index = 0;
    


    for(;;) {

        bits = xEventGroupWaitBits(EventGroupHandle, AUDIO_START_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
        Serial.println("Gun fire task activated");


    
        if(bits & AUDIO_START_BIT){
            
            if(index >= 4) index = 0;


            AudioFileSourcePROGMEM *currentSample = new AudioFileSourcePROGMEM(sample_data[index], sample_lengths[index]);

            if(wav->isRunning()) {
                wav->stop();
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }
            

            Serial.println("Playing sound sample index: " + String(index));
    
            if (!wav->begin(currentSample, out)) {
             Serial.printf("❌ wav->begin() failed for index %d\n", index);
             continue;
                }
            xEventGroupSetBits(EventGroupHandle, AUDIO_PLAYING_BIT);
            index++;
            

            while(wav->isRunning()) {
                bits = xEventGroupGetBits(EventGroupHandle);
            if(bits & AUDIO_INTERRUPT_BIT){
                    Serial.println("Audio interrupted!");
                    wav->stop();
                    // Clear the interrupt bit
                    xEventGroupClearBits(EventGroupHandle, AUDIO_INTERRUPT_BIT);
                    xEventGroupSetBits(EventGroupHandle, AUDIO_START_BIT);
                    delete currentSample;
                    break;
                }
                wav->loop();
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            delete currentSample;
        }
    }
    vTaskDelete(NULL);
}


/*

 if (triggerPressed) {
    triggerPressed = false;
    Serial.println("Trigger pressed!");

    // Stop and clean up if already playing
    if (wav != nullptr && wav->isRunning()) wav->stop();
    if (wav != nullptr) { delete wav; wav = nullptr; }
    if (file2 != nullptr) { delete file2; file2 = nullptr; }

    // Create and start new playback
    file2 = new AudioFileSourcePROGMEM(pulse_16_bit, pulse_16_bit_length);
    wav = new AudioGeneratorWAV();
    wav->begin(file2, out);
    digitalWrite(vibration_pin, HIGH);

  }

  // Keep playback running until the WAV finishes
  if (wav != nullptr && wav->isRunning()) {
    wav->loop(); // this makes it continue playing
  } else if (wav != nullptr) {
    // finished playing, clean up
    delete wav; wav = nullptr;
    delete file2; file2 = nullptr;
    digitalWrite(vibration_pin, LOW);
    Serial.println("Playback finished.");
  }
*/
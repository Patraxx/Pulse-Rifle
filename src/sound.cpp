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

const uint8_t* test_data[2] = {
normal_pulse,
louder_normal
};
const size_t test_lengths[2]{
    normal_pulse_length,
    louder_normal_length
};
#define INDEX_SIZE 2

/* small gain-cycle for quick tests: will rotate through these per-play */
static const float gain_cycle[] = { 1.5f,2.0f, 2.5f };
static const size_t gain_cycle_len = sizeof(gain_cycle)/sizeof(gain_cycle[0]);
static size_t gain_index = 0;


void gainCycleTest() {
      if (out) {
                float g = gain_cycle[gain_index % gain_cycle_len];
                out->SetGain(g);
                Serial.printf("Gain set to %.2f (cycle idx %u)\n", g, (unsigned)gain_index);
                gain_index = (gain_index + 1) % gain_cycle_len;
            }
}

void setupSound() {
   
    wav = new AudioGeneratorWAV();
    out = new AudioOutputI2S();
    out->SetPinout(26, 25, 22);
    out->SetGain(1.0f); // 0.0 .. 4.0
}

void gun_fire_task(void *parameter) {
    setupSound();
    EventBits_t bits;

   int index = 0;
    


    for(;;) {

        bits = xEventGroupWaitBits(EventGroupHandle, AUDIO_START_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
        Serial.println("Gun fire task activated");
        if (testMode == 1){
            index = 0;
        }
           


    
        if(bits & AUDIO_START_BIT){
            
            if(index >= INDEX_SIZE) index = 0;


            if (testMode == 1){
            AudioFileSourcePROGMEM *currentSample = new AudioFileSourcePROGMEM(test_data[index], test_lengths[index]);
            } else {
            AudioFileSourcePROGMEM *currentSample = new AudioFileSourcePROGMEM(sample_data[index], sample_lengths[index]);
            }   

            if(wav->isRunning()) {
                wav->stop();
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }
            

            Serial.println("Playing sound sample index: " + String(index));
            /* Apply cyclic gain for this play (helps quick A/B testing) */
          
    
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
                    break;
                }
                wav->loop();
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            xEventGroupClearBits(EventGroupHandle, AUDIO_PLAYING_BIT);
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
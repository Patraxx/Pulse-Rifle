#include "headers.h"
#include "sound.h"

AudioGeneratorWAV *wav;
/* exported indicator of which sample index is currently requested/playing */
volatile int current_sample_index = 0;

const uint8_t* sample_data[5] = {
pulse_one,
pulse_five,
pulse_two,
pulse_three,
pulse_four

};
const size_t sample_lengths[5] = {
    pulse_one_length,
    pulse_five_length,
    pulse_two_length,
    pulse_three_length,
    pulse_four_length,
};
AudioOutputI2S *out;

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
    out->SetGain(0.8); // 0.0 .. 4.0
}

void gun_fire_task(void *parameter) {
    setupSound();
    EventBits_t bits;



    for(;;) {

        bits = xEventGroupWaitBits(EventGroupHandle, AUDIO_START_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
        Serial.println("Gun fire task activated");

        /* local play index to avoid global name conflicts */
        int index = 0;

        if(bits & AUDIO_START_BIT){
            /* keep index persistent per-task by using a static local */
            static int play_index = 0;
            index = play_index;
            if (index >= INDEX_SIZE) index = 0;

            /* publish the index for other tasks (rumble) */
            current_sample_index = index;

            AudioFileSourcePROGMEM *currentSample = new AudioFileSourcePROGMEM(sample_data[index], sample_lengths[index]);

            if(index == 3) {
                out->SetGain(0.8); // 0.0 .. 4.0
            }
            else {
                out->SetGain(1.0); // 0.0 .. 4.0
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
            play_index = (play_index + 1) % INDEX_SIZE;
            

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
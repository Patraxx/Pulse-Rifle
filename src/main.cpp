#include "headers.h"
#include "pulse.h"

AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *file2;
AudioOutputI2S *out;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Start");

  file2 = new AudioFileSourcePROGMEM(pulse_16_bit, pulse_16_bit_length);
  wav = new AudioGeneratorWAV();
  out = new AudioOutputI2S();
  out->SetPinout(26, 25, 22);
  out->SetGain(0.8); // 0.0 .. 4.0
  wav->begin(file2, out);
  xTaskCreate(
      triggerTask,          // Task function
      "Trigger Task",       // Name of the task (for debugging)
      2048,                 // Stack size (in words)
      NULL,                 // Task input parameter
      1,                    // Priority of the task
      NULL                  // Task handle
  );

}


void loop() {
  // Check trigger once
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
  }

  // Keep playback running until the WAV finishes
  if (wav != nullptr && wav->isRunning()) {
    wav->loop(); // this makes it continue playing
  } else if (wav != nullptr) {
    // finished playing, clean up
    delete wav; wav = nullptr;
    delete file2; file2 = nullptr;
    Serial.println("Playback finished.");
  }
}
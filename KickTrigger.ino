#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// Include your sample here with wav2sketch!
#include "AudioSampleKick.h"

// Teensy Setup
AudioInputI2S            audioInputMono;           //xy=295,416
AudioPlayMemory          sampleInMemory;       //xy=395,489
AudioAnalyzePeak         peakAnalyser;          //xy=484,417
AudioOutputI2S           headphoneOutput;           //xy=502,343

// Patch mono line-in audio jack to peak analyser
AudioConnection          patchCord1(audioInputMono, 0, peakAnalyser, 0);

// Patch mono sample to left channel (if sample is routed to both channels it might result in weird electric noises on the output)
AudioConnection          patchCord2(sampleInMemory, 0, headphoneOutput, 0); // Left Channel
AudioControlSGTL5000     audioShield;     //xy=449,623

const float peakThreshold = 0.65; // everything above this threshold will trigger a sample 
const int cooldown = 50; // cd in ms

unsigned long lastTimeTriggered = 0;
unsigned long currentTime = 0;


void setup() {
  AudioMemory(40);
  audioShield.muteLineout();
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  audioShield.lineInLevel(0);
  audioShield.volume(0.54);
  audioShield.unmuteLineout();
  pinMode(LED_BUILTIN, OUTPUT);
}

// Returns true when cooldown is over (prevents false triggers)
boolean isOnCooldown() {
  if(currentTime - cooldown > lastTimeTriggered) {
    return false;
  }
  
  return true;
}

void loop() {
  currentTime = millis();
  const double readPeak = peakAnalyser.read();

  // Fire Sample if the peak is higher than the set threshold and if trigger is not on cooldown
  if(readPeak > peakThreshold && !isOnCooldown()) {
    // Serial.println(readPeak);
    sampleInMemory.play(AudioSampleKick);

    // Set lastTimeTriggered for isOnCooldown()
    lastTimeTriggered = currentTime;
  }

  // Emit light when audio starts to be close to clipping
  if(readPeak >= peakThreshold) { 
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Set small delay because peakAnalyser would crash otherwise
  delay(10);
}

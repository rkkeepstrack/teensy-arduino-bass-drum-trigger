# Teensy/Arduino Bass Drum Trigger

A small program to play samples based on peaks of incoming audio with threshold and cooldown options. 

This project was created because I started drumming a while ago and wanted to hear the kick drum through my in-ears without the need to set up microphones. Every e-drum module I found on popular music equipment vendors was either very expensive, had not the features I wanted or was the same product like 20 years ago without any improvement (except for the price...). 

So I got a Teensy, started with some simple electronic tutorials with LEDs and then got started writing a little program.

### Final Hardware Setup

The final setup is pretty minimal. I use a very old power brick with a usb-a to micro-usb cable that powers the teensy. The trigger is clipped onto the kick drum which is connected to the soldered mono input jack of the teensy. The output of the teensy audio shield acts as the mono output which I connect to my audio interface with a 3.5mm to 6.3mm jack cable adapter (but can also be the direct output for stage box or IEM rack).

<img width="200" alt="Whole Setup at a glance" src="https://github.com/user-attachments/assets/00d260e4-e9ee-4ac8-acc6-46346aed8a3b" />

The Mono Jack is soldered to the left channel audio input I2S of the audio shield. To prevent the teensy from voltage spikes, there is little 3.3v z-diode circuit with 2 resistors that activates when there are peaks higher than 3.3v.

<img width="200" alt="The Teensy inside" src="https://github.com/user-attachments/assets/4d760751-2589-4a68-857b-1ce2f03e387d" />


### Getting Started

#### Get the required Hardware
- Teensy 4.0 with headers (think of headers like solderless plug&play)
- Teensy Audioshield
- Female Headers, 50pc (to solder onto the Audioshield)
- 0,6 W, 270 Ohm Resistors
- 3.3V Z-Diode (to drain high voltage spikes of the trigger, I heard these could fry your circuit)
- 6.35mm mono jack (take non-switchable ones)
- Breadboard & Cables Starter Kit
- Bass Drum Trigger & Audio Cable
- Power Brick
- Adapter from 3.5mm to 6.3mm jack cable
- Adapter from Micro-USB to something that you want to power your teensy with

  After buying all that, you can get started setting up the hardware on a breadboard to your liking.

#### Load your sample into the memory

Before you can start, you need to load your own kick sample into the project with [wav2sketch](https://github.com/PaulStoffregen/Audio/tree/master/extras/wav2sketch) and include it in the same folder. You have to include the .h file in the Kicktrigger.ino, the name in the .h file has to be the same as in the .cpp file and the cpp file has to start with lines something like this:

```
// Audio data converted from audio file by wav2sketch_js

#include "{{NAME_OF_YOUR_SAMPLE}}.h"
#include <Arduino.h>
// Converted from Kick.wav, using 44100 Hz, 16 bit u-law encoding
PROGMEM
const unsigned int ...
```

The right way of including Samples is also found in the [examples from Paul Stoffregen](https://github.com/PaulStoffregen/Audio/tree/master/examples/SamplePlayer)

#### Avoiding wrong triggerings

If you have issues with wrong triggerings, you can adjust the peakThreshold. Also, raising the cooldown time can help to avoid double triggerings, but for me, a threshold with 0.65 and just a small cooldown worked pretty good.

### Helpful Tools and Resources

- To load your own samples into the memory without using a SD-Card, you need to use [wav2sketch](https://github.com/PaulStoffregen/Audio/tree/master/extras/wav2sketch) and include the files in the same folder, in my case I used a copyrighted sample from a Drumlibrary which is why I can't provide it.
- [Getting Started with teensy](https://learn.sparkfun.com/tutorials/getting-started-with-the-teensy)
- [Audio Design Tool for Teensy](https://www.pjrc.com/teensy/gui/index.html?info=AudioControlSGTL5000#)
- Having an older brother that has a good soldering tool and a 3d printer is really helpful :)


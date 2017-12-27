# circuit-playground-breathing

An app for practicing breathing with the Circuit Playground.

This was based on a video I saw on facebook where someone made a device that helps with practicing your breathing.  It would light up for breathing when you picked it up.  This basically does the same thing.

## Links
- [Learn about the Adafruit Circuit Playground Express](https://learn.adafruit.com/adafruit-circuit-playground-express/downloads?view=all)
- [Buy a Circuit Playrgound Express](https://www.adafruit.com/product/3333)
- [Learn about the Adafruit Circuit Playground Classic](https://learn.adafruit.com/circuit-playground-lesson-number-0/neopixels#circuit-playground-library)
- [Buy a Circuit Playrground Classic](https://www.adafruit.com/product/3000)

*I have no affiliation with Adafruit other than the fact that I think they're pretty awesome.*

## Usage
Just deploy the code to the circuit playground and leave it plugged in or connected to a power source.

When you pick up the device it will be activated by motion on the Z axis.  It will get brighter over 7 seconds, all the lights will cycle for half a second, and then the lights will dim.  The device will continue to do this for 10 times, so just over a minute.

## Modification

Most of the parameters are global variables near the top of the file, so you can easily change them.  Some important notes:

- Time is in ***milliseconds***.
- An iteration in the code is going up ***OR*** down.  So 2 iterations is 1 full cycle.
- `_motionThreshold` is how sensitive the deivce is when being picked up.  I believe the accelerometer is always affected by gravity ~9.8 m/s... so anything less than that *should* trigger the device.  I set it to 7 to mostly avoid bumps setting off the device.
- I think the `delay(50)` is needed for the timeElapsed to actually record a value to track changes over time.

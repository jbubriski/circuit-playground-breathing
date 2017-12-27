// Based on the Circuit Playground Demo program
// For practicing breathing.
// The lights on the Circuit Playgorund will pulse brighter, cycle the LED's, and then dim a bunch of times.

#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include <elapsedMillis.h>

elapsedMillis timeElapsed;

bool _running = false;

float motionThreshold = 7;

float _timeLeftMax = 7000;
float _timeLeft = 0;

bool _up = true;
int _maxIterations = 10;
int _iteration = 0;
int _neoPixelCycle = 0;

int maxBrightness = 255;
int minBrightness = 5;

int _color = 225;

void setup() {
  //  while (!Serial);
  Serial.begin(9600);
  Serial.println("Circuit Playground test!");

  CircuitPlayground.begin();
}


void loop() {
  // test Red #13 LED
  //  CircuitPlayground.redLED(HIGH);
  //  delay(100);
  //  CircuitPlayground.redLED(LOW);
  delay(50);

  /************* TEST CAPTOUCH */

  //Serial.print("Capsense #3: "); Serial.println(CircuitPlayground.readCap(3));
  //  Serial.print("Capsense #2: "); Serial.println(CircuitPlayground.readCap(2));
  //  Serial.print("Capsense #0: "); Serial.println(CircuitPlayground.readCap(0));
  //  Serial.print("Capsense #1: "); Serial.println(CircuitPlayground.readCap(1));
  //  Serial.print("Capsense #12: "); Serial.println(CircuitPlayground.readCap(12));
  //  Serial.print("Capsense #6: "); Serial.println(CircuitPlayground.readCap(6));
  //  Serial.print("Capsense #9: "); Serial.println(CircuitPlayground.readCap(9));
  //  Serial.print("Capsense #10: "); Serial.println(CircuitPlayground.readCap(10));

  /************* TEST SLIDE SWITCH */
  //  if (CircuitPlayground.slideSwitch()) {
  //    Serial.println("Slide to the left");
  //  } else {
  //    Serial.println("Slide to the right");
  //    CircuitPlayground.playTone(500 + pixeln * 500, 250);
  //  }

  _timeLeft -= timeElapsed;

  Serial.println(_timeLeft);
  Serial.println(timeElapsed);

  if (!_running && _timeLeft <= 0 && CircuitPlayground.motionZ() < motionThreshold) {
    // Start!
    // Reset everything
    _running = true;
    _timeLeft = _timeLeftMax;
    _iteration = 0;
    _up = true;
  } else if (_running && _timeLeft <= 0 && _iteration > _maxIterations) {
    // All done!
    CircuitPlayground.clearPixels();
    _running = false;
  } else if (_running && _timeLeft <= -500) {
    // Iteration done with up!
    _timeLeft = _timeLeftMax;
    _up = !_up;
    _iteration++;
  } else if (_running && _timeLeft <= 0 && _up) {
    // Cycle colors before going back down
    CircuitPlayground.clearPixels();

    CircuitPlayground.setPixelColor(_neoPixelCycle, CircuitPlayground.colorWheel(_color));
    _neoPixelCycle++;

    if (_neoPixelCycle > 10)
      _neoPixelCycle = 0;

    Serial.println("Cycling...");
  }  else if (_running && _timeLeft <= 0 && !_up) {
    // Iteration done with down
    _timeLeft = _timeLeftMax;
    _up = !_up;
    _iteration++;
  } else if (_running) {
    // Running, adjust brightness
    if (_up) {
      float brightness = ((_timeLeftMax - _timeLeft) / _timeLeftMax * (maxBrightness - minBrightness)) + minBrightness;

      CircuitPlayground.setBrightness(brightness);

      for (int i = 0; i < 11; i++) {
        CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(_color));
      }

      Serial.println("Brighter...");
      Serial.println("Brightness " + String(brightness));
    } else {
      float brightness = (_timeLeft / _timeLeftMax * (maxBrightness - minBrightness)) + minBrightness;

      CircuitPlayground.setBrightness(brightness);

      for (int i = 0; i < 11; i++) {
        CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(_color));
      }

      Serial.println("Dimmer...");
      Serial.println("Brightness " + String(brightness));
    }
  }

  /************* TEST BOTH BUTTONS */
  if (CircuitPlayground.leftButton()) {
    Serial.println("Left button pressed!");
    _color -= 15;

    if (_color < 0) {
      _color = 255 + _color;
    }
  }
  if (CircuitPlayground.rightButton()) {
    Serial.println("Right button pressed!");
    _color += 15;

    if (_color > 255) {
      _color = _color - 255;
    }
  }

  /************* TEST LIGHT SENSOR */
  //  Serial.print("Light sensor: ");
  //  Serial.println(CircuitPlayground.lightSensor());

  /************* TEST SOUND SENSOR */
  //  Serial.print("Sound sensor: ");
  //  Serial.println(CircuitPlayground.soundSensor());

  /************* TEST ACCEL */
  // Display the results (acceleration is measured in m/s*s)
  //  Serial.print("X: "); Serial.print(CircuitPlayground.motionX());
  //  Serial.print(" \tY: "); Serial.print(CircuitPlayground.motionY());
  //  Serial.print(" \tZ: "); Serial.print(CircuitPlayground.motionZ());
  //  Serial.println(" m/s^2");

  /************* TEST THERMISTOR */
  //  Serial.print("Temperature ");
  //  Serial.print(CircuitPlayground.temperature());
  //  Serial.println(" *C");

  // Reset timeElapsed so it doesn't accumulate
  timeElapsed = 0;
}

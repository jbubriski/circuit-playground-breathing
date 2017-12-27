// Based on the Circuit Playground Demo program
// For practicing breathing.
// The lights on the Circuit Playgorund will pulse brighter, cycle the LED's, and then dim a bunch of times.

#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include <elapsedMillis.h>

// Don't change these state variables
elapsedMillis timeElapsed;
bool _running = false;
float _timeLeft = 0;
bool _up = true;
int _maxIterations = 10;
int _iteration = 0;
int _neoPixelCycle = 0;

// Change this to change how sensitive the "pickup" speed needs to be
float _motionThreshold = 7;

// Change this to change how long each iteration (up or down) is.
// Value is in millisecond.  Ex 7000 = 7 seconds.
float _timeLeftMax = 7000;

// Change these values to change how dim/bright the CP gets during a cycle
int _maxBrightness = 255;
int _minBrightness = 5;

// Change this value to change the color of the CP
int _color = 225;

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to the breathing app");

  CircuitPlayground.begin();
}

void loop() {
  delay(50);

  _timeLeft -= timeElapsed;

  Serial.println(_timeLeft);
  Serial.println(timeElapsed);

  if (!_running && _timeLeft <= 0 && CircuitPlayground.motionZ() < _motionThreshold) {
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
      float brightness = ((_timeLeftMax - _timeLeft) / _timeLeftMax * (_maxBrightness - _minBrightness)) + _minBrightness;

      CircuitPlayground.setBrightness(brightness);

      for (int i = 0; i < 11; i++) {
        CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(_color));
      }

      Serial.println("Brighter...");
      Serial.println("Brightness " + String(brightness));
    } else {
      float brightness = (_timeLeft / _timeLeftMax * (_maxBrightness - _minBrightness)) + _minBrightness;

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

  // Reset timeElapsed so it doesn't accumulate
  timeElapsed = 0;
}

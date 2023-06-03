# AnalogWrite
This library provides an analogWrite function qand Servo support for ESP32

About
This library provides an analogWrite function polyfill for ESP32 Arduino framework by wrapping the ledc library.

Licensed under the MIT license.

Usage
The library will do all the timer setup and channel selection work behind the scene so you don't have to worry about that.

Fade Example
#include <Arduino.h>
#include <analogWrite.h>

int step = 1;
int brightness = 0;

void setup() {
}

void loop() {
  brightness += brightStep;
  analogWrite(LED_BUILTIN, brightness);

  if ( brightness == 0 || brightness == 255 ) {
    brightStep = -brightStep;
  }
  
  delay(10);
}
Default Value Range
Call the analogWrite function like in standard arduino framework:

analogWrite(LED_BUILTIN, 255); // value range 0-255 so 255 = 100%
Custom Value Range
You can also set the maximum value as third parameter:

analogWrite(LED_BUILTIN, 255, 1023); // value range 0-1023 so 255 = 25%
Timer Resolution
The default timer resolution is set to 13 bits in all the 16 channels, if you want to change that, use the analogWriteResolution function:

analogWriteResolution(10); // set resolution to 10 bits for all pins
analogWriteResolution(LED_BUILTIN, 10); // set resolution to 10 bits for LED pin
PWM Frequency
The default PWM frequency is set to 5000 Hz in all the 16 channels, if you want to change that, use the analogWriteFrequency function:

analogWriteFrequency(10000); // set frequency to 10 KHz for all pins
analogWriteFrequency(LED_BUILTIN, 10000); // set frequency to 10 KHz for LED pin
Please note that both timer resolution and PWM frequency should be calculated to get the expected results, if frequency is not set correctly, the output PWM signal wont be as expected, read more about Supported Range of Frequency and Duty Resolution in the official Espressif documentation website.

analogServo(2, 90) // Send 90 degrees control signal to servo connected to pin 2 (0 degrees = 600ms 180 degrees = 2400ms at 50Hz)
analogServo(2, 500) // Send 500ms control signal to servo connected to pin 2 (if second argument > 200 then is converted to ms at 50Hz)

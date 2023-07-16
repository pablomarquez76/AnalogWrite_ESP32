/*

All pin numbers are allowed, but pins 2,4,12-13,16-19,21-23,25-27,32-33 are recommended.
Remember that pins 0,1,3,5,14-15 are HIGH at boot, pins 1,3 are also used for Serial 
communication, pins 34-36 and 39 are input only pins.

In tone function the maximum frequency is 7800Hz and maximum duration is 2000ms (2s).

In analogServo function values are treated as follows:
            Value                                   Becomes
            -----                                   -------
            0 - 180                             value (treated as degrees)
            181 - 3999                          value (treated as microseconds)
            4000 and up                             pin output LOW

*/

#ifndef analogWrite_ESP32_h
#define analogWrite_ESP32_h


#include <Arduino.h>

typedef struct analog_write_channel {
  int8_t pin;
  uint32_t frequency;
  uint8_t resolution;
} analog_write_channel_t;

uint8_t analogWriteChannel(int8_t pin);

void updatePins();

void analogWriteFrequency(uint32_t frequency);
void analogWriteFrequency(int8_t pin, uint32_t frequency);

void analogWriteResolution(uint8_t resolution);
void analogWriteResolution(int8_t pin, uint8_t resolution);

void analogWrite(int8_t pin, uint32_t value);

void analogServo(int8_t pin, uint32_t value);

void tone(int8_t pin, uint32_t freq);
void tone(int8_t pin, uint32_t freq, uint32_t duration);
void notone(int8_t pin);

#endif

#include <Arduino.h>

typedef struct analog_write_channel
{
  int8_t pin;
  uint32_t frequency;
  uint8_t resolution;
} analog_write_channel_t;

int analogWriteChannel(uint8_t pin);

void updatePins();

void analogWriteFrequency(uint32_t frequency);
void analogWriteFrequency(uint8_t pin, uint32_t frequency);

void analogWriteResolution(uint8_t resolution);
void analogWriteResolution(uint8_t pin, uint8_t resolution);

void analogWrite(uint8_t pin, uint32_t value);

void analogServo(uint8_t pin, uint32_t value);

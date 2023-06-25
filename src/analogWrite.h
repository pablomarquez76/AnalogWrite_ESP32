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

#include "analogWrite.h"

#define TONE_DUTY 511
#define MAX_TONE_FREQ 7800
#define MAX_TONE_DURATION 2000
#define TONE_RESOLUTION 10

#define NUM_CHANNELS 16
#define MAX_RESOLUTION 16
#define SERVO_FREQUENCY 50
#define SERVO_RESOLUTION 12

#define SERVO_MAX_ANGLE 180
#define SERVO_MIN_TICKS 102
#define SERVO_MAX_TICKS 512
#define SERVO_MIN_PULSE_WIDTH 498
#define SERVO_MAX_PULSE_WIDTH 2500
#define SERVO_OVERFLOW_PULSE_WIDTH 4000

analog_write_channel_t _analog_write_channels[NUM_CHANNELS] = {
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 },
  { -1, 5000, 8 }
};

uint8_t analogWriteChannel(int8_t pin) {
  uint8_t channel = NUM_CHANNELS;
  // Check if pin already attached to a channel
  for (uint8_t i = 0; i < NUM_CHANNELS; i++) {
    if (_analog_write_channels[i].pin == pin) {
      channel = i;
      break;
    }
  }
  // If not, attach it to a free channel
  if (channel == NUM_CHANNELS) {
    for (uint8_t i = 0; i < NUM_CHANNELS; i++) {
      if (_analog_write_channels[i].pin == -1) {
        _analog_write_channels[i].pin = pin;
        channel = i;
        ledcSetup(channel, _analog_write_channels[i].frequency, _analog_write_channels[i].resolution);
        ledcAttachPin(pin, channel);
        break;
      }
    }
  }
  return channel;
}

void updatePins() {
  for (uint8_t channel = 0; channel < NUM_CHANNELS; channel++) {
    if (_analog_write_channels[channel].pin != -1) {
      ledcSetup(channel, _analog_write_channels[channel].frequency, _analog_write_channels[channel].resolution);
      ledcAttachPin(_analog_write_channels[channel].pin, channel);
    }
  }
}

void analogWriteFrequency(uint32_t frequency) {
  for (uint8_t i = 0; i < NUM_CHANNELS; i++) {
    _analog_write_channels[i].frequency = frequency;
  }
  updatePins();
}

void analogWriteFrequency(int8_t pin, uint32_t frequency) {
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < NUM_CHANNELS) {
    _analog_write_channels[channel].frequency = frequency;  // max 80000000 / 2^bit_num
    ledcSetup(channel, _analog_write_channels[channel].frequency, _analog_write_channels[channel].resolution);
  }
}

void analogWriteResolution(uint8_t resolution) {
  if (resolution < 1) resolution = 1;
  else if (resolution > MAX_RESOLUTION) resolution = MAX_RESOLUTION;
  for (uint8_t i = 0; i < NUM_CHANNELS; i++) {
    _analog_write_channels[i].resolution = resolution;  // <=16
  }
  updatePins();
}

void analogWriteResolution(int8_t pin, uint8_t resolution) {
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < NUM_CHANNELS) {
    if (resolution < 1) resolution = 1;
    else if (resolution > MAX_RESOLUTION) resolution = MAX_RESOLUTION;
    _analog_write_channels[channel].resolution = resolution;  // <=16
    ledcSetup(channel, _analog_write_channels[channel].frequency, _analog_write_channels[channel].resolution);
  }
}

void analogWrite(int8_t pin, uint32_t value) {
  // Get channel
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < NUM_CHANNELS) {
    ledcWrite(channel, value);
  }
}

void analogServo(int8_t pin, uint32_t value) {
  // Get channel
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < NUM_CHANNELS) {
    // Set frequency and resolution
    if (_analog_write_channels[channel].frequency != SERVO_FREQUENCY || _analog_write_channels[channel].resolution != SERVO_RESOLUTION) {
      _analog_write_channels[channel].frequency = SERVO_FREQUENCY;
      _analog_write_channels[channel].resolution = SERVO_RESOLUTION;
      ledcSetup(channel, _analog_write_channels[channel].frequency, _analog_write_channels[channel].resolution);
    }
    if (value < SERVO_MAX_ANGLE + 1) {
      ledcWrite(channel, map(value, 0, SERVO_MAX_ANGLE, SERVO_MIN_TICKS, SERVO_MAX_TICKS));  // 102:498ms 512:2500ms
    } else if (value < SERVO_OVERFLOW_PULSE_WIDTH) {
      ledcWrite(channel, map(value, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH, SERVO_MIN_TICKS, SERVO_MAX_TICKS));  // map ms to ticks
    } else {
      ledcWrite(channel, 0);
    }
  }
}

void tone(int8_t pin, uint32_t freq) {
  // Get channel
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < NUM_CHANNELS) {
    // Set frequency and resolution
    if (freq < MAX_TONE_FREQ) {  // max freq 7800Hz
      ledcSetup(channel, freq, TONE_RESOLUTION);
      ledcWrite(channel, TONE_DUTY);
    }
  }
}

void tone(int8_t pin, uint32_t freq, uint32_t duration) {  // this is a blocking function
  // Get channel
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < NUM_CHANNELS) {
    // Set frequency and resolution
    if (freq < MAX_TONE_FREQ && duration < MAX_TONE_DURATION) {  // max freq 7800Hz max duration 2000ms
      uint32_t ms = millis();
      ledcSetup(channel, freq, TONE_RESOLUTION);
      ledcWrite(channel, TONE_DUTY);
      while (millis() - ms < duration) delay(1);
      ledcWrite(channel, 0);
    }
  }
}

void notone(int8_t pin) {
  // Get channel
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < NUM_CHANNELS) {
    // Set frequency and resolution
    ledcSetup(channel, 3000, TONE_RESOLUTION);
    ledcWrite(channel, 0);
  }
}

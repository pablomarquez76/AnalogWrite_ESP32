#include "analogWrite.h"

analog_write_channel_t _analog_write_channels[16] = {
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
  uint8_t channel = 16;
  // Check if pin already attached to a channel
  for (uint8_t i = 0; i < 16; i++) {
    if (_analog_write_channels[i].pin == pin) {
      channel = i;
      break;
    }
  }
  // If not, attach it to a free channel
  if (channel == 16) {
    for (uint8_t i = 0; i < 16; i++) {
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
  for (uint8_t channel = 0; channel < 16; channel++) {
    if (_analog_write_channels[channel].pin != -1) {
      ledcSetup(channel, _analog_write_channels[channel].frequency, _analog_write_channels[channel].resolution);
      ledcAttachPin(_analog_write_channels[channel].pin, channel);
    }
  }
}

void analogWriteFrequency(uint32_t frequency) {
  for (uint8_t i = 0; i < 16; i++) {
    _analog_write_channels[i].frequency = frequency;
  }
  updatePins();
}

void analogWriteFrequency(int8_t pin, uint32_t frequency) {
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < 16) {
    _analog_write_channels[channel].frequency = frequency;  // max 80000000 / 2^bit_num
    ledcSetup(channel, _analog_write_channels[channel].frequency, _analog_write_channels[channel].resolution);
  }
}

void analogWriteResolution(uint8_t resolution) {
  if (resolution < 1) resolution = 1;
  else if (resolution > 16) resolution = 16;
  for (uint8_t i = 0; i < 16; i++) {
    _analog_write_channels[i].resolution = resolution;  // <=16
  }
  updatePins();
}

void analogWriteResolution(int8_t pin, uint8_t resolution) {
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < 16) {
    if (resolution < 1) resolution = 1;
    else if (resolution > 16) resolution = 16;
    _analog_write_channels[channel].resolution = resolution;  // <=16
    ledcSetup(channel, _analog_write_channels[channel].frequency, _analog_write_channels[channel].resolution);
  }
}

void analogWrite(int8_t pin, uint32_t value) {
  // Get channel
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < 16) {
    ledcWrite(channel, value);
  }
}

void analogServo(int8_t pin, uint32_t value) {
  // Get channel
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < 16) {
    // Set frequency and resolution
    if (_analog_write_channels[channel].frequency != 50 || _analog_write_channels[channel].resolution != 12) {
      _analog_write_channels[channel].frequency = 50;
      _analog_write_channels[channel].resolution = 12;
      ledcSetup(channel, _analog_write_channels[channel].frequency, _analog_write_channels[channel].resolution);
    }
    if (value < 200) {
      ledcWrite(channel, map(value, 0, 180, 123, 492));
    } else if (value < 4000) {
      ledcWrite(channel, map(value, 600, 2400, 123, 492));
    } else {
      ledcWrite(channel, 0);
    }
  }
}

void tone(int8_t pin, uint32_t freq) {
  // Get channel
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < 16) {
    // Set frequency and resolution
    if (freq < 7800) {  // max freq 7800Hz
      ledcSetup(channel, freq, 10);
      ledcWrite(channel, 511);
    }
  }
}

void tone(int8_t pin, uint32_t freq, uint32_t duration) {  // this is a blocking function
  // Get channel
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < 16) {
    // Set frequency and resolution
    if (freq < 7800 && duration < 2000) {  // max freq 7800Hz max duration 2000ms
      uint32_t ms = millis();
      ledcSetup(channel, freq, 10);
      ledcWrite(channel, 511);
      while (millis() - ms < duration) delay(1);
      ledcWrite(channel, 0);
    }
  }
}

void notone(int8_t pin) {
  // Get channel
  uint8_t channel = analogWriteChannel(pin);
  // Make sure the pin was attached to a channel, if not do nothing
  if (channel < 16) {
    // Set frequency and resolution
    ledcSetup(channel, 5000, 8);
    ledcWrite(channel, 0);
  }
}

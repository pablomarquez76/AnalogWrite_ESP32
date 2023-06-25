#include <Arduino.h>
#include <analogWrite.h>

#define PIN_SERVO 22

void setup() {
  // Set resolution for a specific pin
  pinMode(PIN_SERVO, OUTPUT);
}

void loop() {
  // Move servo using angles
  analogServo(PIN_SERVO, 0);
  delay(1000);
  analogServo(PIN_SERVO, 180);
  delay(1000);
  // Move servo using milliseconds
  analogServo(PIN_SERVO, 600);
  delay(1000);
  analogServo(PIN_SERVO, 2400);
  delay(1000);
  analogServo(PIN_SERVO, 4000);  // >=4000 dettach
  delay(4000);
}

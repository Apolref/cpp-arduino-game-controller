/*
  game_controller.ino

  Simple Arduino firmware for a custom game controller.
  It reads a set of digital buttons and sends their state
  as a single byte (bitmask) over the serial port.

  Bit mapping (from LSB to MSB):
    bit 0 -> UP
    bit 1 -> DOWN
    bit 2 -> LEFT
    bit 3 -> RIGHT
    bit 4 -> A
    bit 5 -> B
*/

#include <Arduino.h>

const uint8_t NUM_BUTTONS = 6;
const uint8_t buttonPins[NUM_BUTTONS] = {
  2, // UP
  3, // DOWN
  4, // LEFT
  5, // RIGHT
  6, // A
  7  // B
};

void setup() {
  Serial.begin(115200);

  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // button to GND
  }
}

void loop() {
  uint8_t mask = 0;

  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    // INPUT_PULLUP => LOW means pressed
    if (digitalRead(buttonPins[i]) == LOW) {
      mask |= (1 << i);
    }
  }

  Serial.write(mask);  // send 1 byte
  delay(10);           // ~100 Hz update rate
}

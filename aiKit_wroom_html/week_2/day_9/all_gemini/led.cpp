#include "Arduino.h"
#include "led.h"

// Constructor
LedControl::LedControl(int pin) {
    ledPin = pin;
}

// Set up the pin mode.
// This is done separately from the constructor to allow the user
// to call it at a specific point in the setup() function.
void LedControl::setupPin() {
    pinMode(ledPin, OUTPUT);
    // Initialize the LED to OFF
    digitalWrite(ledPin, HIGH);
}

// Turn on the LED (active low)
void LedControl::turnOn() {
    digitalWrite(ledPin, LOW);
}

// Turn off the LED (active low)
void LedControl::turnOff() {
    digitalWrite(ledPin, HIGH);
}


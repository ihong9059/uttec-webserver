#include "Arduino.h"
#include "led.h"

// Constructor
LedControl::LedControl(int pin) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
}

void LedControl::initRed(){
    pinMode(ledPin, OUTPUT);
}

// Turn on the LED (active low)
void LedControl::turnOn() {
    digitalWrite(ledPin, LOW);
}

// Turn off the LED (active low)
void LedControl::turnOff() {
    digitalWrite(ledPin, HIGH);
}

// Get the pin number
int LedControl::getPin() {
    return ledPin;
}


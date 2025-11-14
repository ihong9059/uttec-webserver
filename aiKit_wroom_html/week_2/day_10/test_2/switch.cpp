#include "switch.h"

Switch::Switch(int switchPin) {
  pin = switchPin;
  state = false;
  lastButtonState = HIGH;
  lastDebounceTime = 0;
  debounceDelay = 50;
}

void Switch::begin() {
  pinMode(pin, INPUT_PULLUP);
  state = digitalRead(pin);
}

void Switch::read() {
  bool reading = digitalRead(pin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != state) {
      state = reading;
    }
  }
  
  lastButtonState = reading;
}

bool Switch::getState() {
  return state;
}

bool Switch::isPressed() {
  return state == LOW;  // PULLUP이므로 LOW가 눌린 상태
}

bool Switch::isReleased() {
  return state == HIGH; // PULLUP이므로 HIGH가 떨어진 상태
}


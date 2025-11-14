#include "switch.h"

Switch::Switch(int pin) {
    this->pin = pin;
    this->lastState = HIGH; // 풀업 저항 사용 가정
    this->lastDebounceTime = 0;
    this->debounceDelay = 50;
}

void Switch::begin() {
    pinMode(pin, INPUT_PULLUP);
}

bool Switch::read() {
    int reading = digitalRead(pin);
    
    // 디바운싱 처리
    if (reading != lastState) {
        lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != lastState) {
            lastState = reading;
            return reading;
        }
    }
    
    return lastState;
}

bool Switch::isPressed() {
    return (read() == LOW); // 눌렸을 때 LOW
}

bool Switch::stateChanged() {
    static bool previousState = HIGH;
    bool currentState = read();
    
    if (currentState != previousState) {
        previousState = currentState;
        return true;
    }
    return false;
}
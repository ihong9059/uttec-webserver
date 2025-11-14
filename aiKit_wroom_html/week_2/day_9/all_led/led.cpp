// led.cpp
#include "led.h"

Led::Led(int ledPin, String ledColor) {
    pin = ledPin;
    state = false;
    color = ledColor;
}

void Led::begin() {
    pinMode(pin, OUTPUT);
    off(); // 초기 상태는 꺼짐
}

void Led::on() {
    digitalWrite(pin, LOW); // LOW에서 LED ON
    state = true;
    Serial.println(color + " LED ON");
}

void Led::off() {
    digitalWrite(pin, HIGH); // HIGH에서 LED OFF
    state = false;
    Serial.println(color + " LED OFF");
}

void Led::toggle() {
    if (state) {
        off();
    } else {
        on();
    }
    Serial.println(color + " LED TOGGLE: " + String(state ? "ON" : "OFF"));
}

bool Led::getState() {
    return state;
}

String Led::getColor() {
    return color;
}


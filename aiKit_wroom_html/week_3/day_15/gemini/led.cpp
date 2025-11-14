#include <Arduino.h>
#include "led.h"

#define RED_LED_PIN 25
#define YELLOW_LED_PIN 26
#define BLUE_LED_PIN 27

void setupLeds() {
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
}

void controlLed(char color, int value) {
    int pin = -1;
    switch (color) {
        case 'R':
            pin = RED_LED_PIN;
            break;
        case 'Y':
            pin = YELLOW_LED_PIN;
            break;
        case 'B':
            pin = BLUE_LED_PIN;
            break;
        default:
            return;
    }
    // Low-Active(0V에서 ON) 극성으로 변경
    // 0을 입력하면 255-0 = 255(OFF)
    // 255를 입력하면 255-255 = 0(ON)
    analogWrite(pin, 255 - value);
}
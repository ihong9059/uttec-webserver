#ifndef LED_H
#define LED_H

class LedControl {
public:
    // Constructor to set up the pin
    LedControl(int pin);

    // Method to set up the pin mode.
    void setupPin();

    // Method to turn on the LED (active low)
    void turnOn();

    // Method to turn off the LED (active low)
    void turnOff();

private:
    int ledPin;
};

#endif
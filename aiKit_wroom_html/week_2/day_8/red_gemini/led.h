#ifndef LED_H
#define LED_H

class LedControl {
public:
    // Constructor to set up the pin
    LedControl(int pin);
    
    void initRed();
    // 이것은 uttec이 추가 한것입니다. 2025.09.21
    
    // Method to turn on the LED (active low)
    void turnOn();

    // Method to turn off the LED (active low)
    void turnOff();

    // Get the pin number
    int getPin();
    
private:
    int ledPin;
};

#endif

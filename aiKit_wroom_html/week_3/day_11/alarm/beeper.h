#ifndef BEEPER_H
#define BEEPER_H

#include <Arduino.h>

class Beeper {
  private:
    int beepPin;
    bool isBeeping;
    unsigned long beepStartTime;
    unsigned long beepDuration;
    
  public:
    Beeper(int pin);
    void begin();
    void beep(unsigned long duration);
    void update();
    bool isActive();  // beep 상태 확인 메서드 추가
};

#endif


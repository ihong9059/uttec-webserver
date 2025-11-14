#ifndef LED_H
#define LED_H

class LedControl {
public:
    // 생성자 (핀 번호 설정)
    LedControl(int pin);

    // 핀 모드 설정
    void setupPin();

    // LED 켜기 (최대 밝기)
    void turnOn();

    // LED 끄기
    void turnOff();

    // LED 밝기 조절 (0~255)
    void setBrightness(int brightness);

private:
    int ledPin;
};

#endif


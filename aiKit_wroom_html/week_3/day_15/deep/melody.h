#ifndef MELODY_H
#define MELODY_H

#include <Arduino.h>

class Melody {
private:
    int beeperPin;
    int speakerPin;
    bool isPlaying;
    
public:
    Melody(int beeperPin, int speakerPin);
    void begin();
    void beep(int duration = 500);
    void playTone(int note, int duration);
    void playMelody(const int melody[], const int noteDurations[], int length);
    void stop();
    bool getIsPlaying();
};

#endif
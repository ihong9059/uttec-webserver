#include "melody.h"
#include "notes.h"

Melody::Melody(int beeperPin, int speakerPin) {
    this->beeperPin = beeperPin;
    this->speakerPin = speakerPin;
    this->isPlaying = false;
}

void Melody::begin() {
    pinMode(beeperPin, OUTPUT);
    pinMode(speakerPin, OUTPUT);
    digitalWrite(beeperPin, HIGH); // LOW에서 동작하므로 시작시 HIGH
    digitalWrite(speakerPin, LOW);
    noTone(speakerPin); // 초기화
}

void Melody::beep(int duration) {
    digitalWrite(beeperPin, LOW);
    delay(duration);
    digitalWrite(beeperPin, HIGH);
}

void Melody::playTone(int note, int duration) {
    if (note == REST) {
        noTone(speakerPin);
        delay(duration);
    } else {
        tone(speakerPin, note);
        delay(duration);
        noTone(speakerPin);
    }
}

void Melody::playMelody(const int melody[], const int noteDurations[], int length) {
    isPlaying = true;
    
    for (int thisNote = 0; thisNote < length; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        playTone(melody[thisNote], noteDuration);
        
        // 음과 음 사이에 약간의 간격을 둠
        delay(noteDuration * 0.3);
        
        // 중간에 멈출 수 있도록 체크
        if (!isPlaying) break;
    }
    
    noTone(speakerPin);
    isPlaying = false;
}

void Melody::stop() {
    isPlaying = false;
    noTone(speakerPin);
    digitalWrite(beeperPin, HIGH); // 버저도 끄기
}

bool Melody::getIsPlaying() {
    return isPlaying;
}


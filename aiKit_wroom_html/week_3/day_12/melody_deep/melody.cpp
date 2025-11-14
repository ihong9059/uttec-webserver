#include "melody.h"
#include "led.h"
#include "notes.h"
#include <Arduino.h>

const int SPEAKER_PIN = 33;

// 현재 재생 상태
bool isPlaying = false;
int currentMelody = 0;
int currentNote = 0;
unsigned long previousNoteTime = 0;
int noteDuration = 0;

// 멜로디 1: 생일 축하곡 (20초)
const int melody1[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4,
  
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};

const int noteDurations1[] = {
  4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 1,
  
  4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 1
};

// 멜로디 2: 작은 별 (20초)
const int melody2[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};

const int noteDurations2[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2
};

// 멜로디 3: 즐거운 나의 집 (20초)
const int melody3[] = {
  NOTE_C4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_F4, NOTE_C4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_C4,
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_F4, NOTE_C4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_C4
};

const int noteDurations3[] = {
  4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 2
};

// 멜로디 4: 도레미송 (20초)
const int melody4[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4,
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_C4,
  NOTE_D4, NOTE_F4, NOTE_A4, NOTE_D5, NOTE_D5, NOTE_A4, NOTE_F4, NOTE_D4,
  NOTE_E4, NOTE_G4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_G4, NOTE_E4
};

const int noteDurations4[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4
};

// 멜로디 5: 영화 메인 테마 (20초)
const int melody5[] = {
  NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3, NOTE_C4,
  NOTE_D4, NOTE_A3, NOTE_D4, NOTE_A3, NOTE_D4, NOTE_A3, NOTE_D4,
  NOTE_E4, NOTE_B3, NOTE_E4, NOTE_B3, NOTE_E4, NOTE_B3, NOTE_E4,
  NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4,
  NOTE_G4, NOTE_D4, NOTE_G4, NOTE_D4, NOTE_G4, NOTE_D4, NOTE_G4
};

const int noteDurations5[] = {
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4
};

// 멜로디 6: 게임 BGM (20초)
const int melody6[] = {
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_A4, NOTE_D5, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_G4, NOTE_B4, NOTE_E5, NOTE_B4, NOTE_G4,
  NOTE_F4, NOTE_A4, NOTE_C5, NOTE_F5, NOTE_C5, NOTE_A4,
  NOTE_G4, NOTE_B4, NOTE_D5, NOTE_G5, NOTE_D5, NOTE_B4,
  NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A5, NOTE_E5, NOTE_C5
};

const int noteDurations6[] = {
  4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4
};

void setupSpeaker() {
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(SPEAKER_PIN, LOW);
}

void playMelody(int number) {
  if (number >= 1 && number <= 6) {
    currentMelody = number;
    currentNote = 0;
    isPlaying = true;
    previousNoteTime = millis();
    noteDuration = 0; // 첫 번째 음표 바로 시작
  }
}

void updateMelody() {
  if (!isPlaying) return;

  unsigned long currentTime = millis();
  
  if (currentTime - previousNoteTime >= noteDuration) {
    // 다음 음표로 이동
    const int* melody = nullptr;
    const int* durations = nullptr;
    int length = 0;

    switch (currentMelody) {
      case 1: melody = melody1; durations = noteDurations1; length = sizeof(melody1)/sizeof(melody1[0]); break;
      case 2: melody = melody2; durations = noteDurations2; length = sizeof(melody2)/sizeof(melody2[0]); break;
      case 3: melody = melody3; durations = noteDurations3; length = sizeof(melody3)/sizeof(melody3[0]); break;
      case 4: melody = melody4; durations = noteDurations4; length = sizeof(melody4)/sizeof(melody4[0]); break;
      case 5: melody = melody5; durations = noteDurations5; length = sizeof(melody5)/sizeof(melody5[0]); break;
      case 6: melody = melody6; durations = noteDurations6; length = sizeof(melody6)/sizeof(melody6[0]); break;
    }

    if (currentNote >= length) {
      // 멜로디 끝
      noTone(SPEAKER_PIN);
      setRedLED(0);
      setYellowLED(0);
      setBlueLED(0);
      isPlaying = false;
      return;
    }

    // 현재 음표 재생
    int note = melody[currentNote];
    int duration = 1000 / durations[currentNote]; // ms 단위로 변환
    
    if (note == REST) {
      noTone(SPEAKER_PIN);
    } else {
      tone(SPEAKER_PIN, note);
    }

    // LED 시각화 (순차적으로 점등)
    if (currentNote % 3 == 0) {
      setRedLED(255);
      setYellowLED(0);
      setBlueLED(0);
    } else if (currentNote % 3 == 1) {
      setRedLED(0);
      setYellowLED(255);
      setBlueLED(0);
    } else {
      setRedLED(0);
      setYellowLED(0);
      setBlueLED(255);
    }

    previousNoteTime = currentTime;
    noteDuration = duration * 0.9; // 음표 길이의 90% 동안 재생
    currentNote++;
  }
}

void stopMelody() {
  noTone(SPEAKER_PIN);
  isPlaying = false;
  setRedLED(0);
  setYellowLED(0);
  setBlueLED(0);
}
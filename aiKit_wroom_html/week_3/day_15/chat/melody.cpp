#include "melody.h"
#include "notes.h"

void melodyInit() {
  pinMode(BEEPER_PIN, OUTPUT);
  digitalWrite(BEEPER_PIN, HIGH); // HIGH=OFF
  pinMode(SPEAKER_PIN, OUTPUT);
  noTone(SPEAKER_PIN);
}

// --- Alarm (0.5초 beep) ---
void playAlarm() {
  digitalWrite(BEEPER_PIN, LOW);
  delay(500);
  digitalWrite(BEEPER_PIN, HIGH);
}

// --- 멜로디 정의 ---
static int melody1[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_REST };
static int noteDur1[] = { 300,    300,     300,     300,     600,    200 };

static int melody2[] = { NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_REST };
static int noteDur2[] = { 300,    300,     300,     300,     600,    200 };

static int melody3[] = { NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_REST };
static int noteDur3[] = { 300,    300,     300,     300,     600,    200 };

static int melody4[] = { NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_G4, NOTE_REST };
static int noteDur4[] = { 300,    300,     300,     300,     600,    200 };

// 멜로디 재생 함수
static void playSong(int* notes, int* durations, int length) {
  for (int i = 0; i < length; i++) {
    int n = notes[i];
    int d = durations[i];
    if (n == NOTE_REST) {
      noTone(SPEAKER_PIN);
    } else {
      tone(SPEAKER_PIN, n, d);
    }
    delay(d * 1.3); // note 간 간격
  }
  noTone(SPEAKER_PIN);
}

void playMelody(uint8_t id) {
  switch(id) {
    case 1: playSong(melody1, noteDur1, sizeof(melody1)/sizeof(int)); break;
    case 2: playSong(melody2, noteDur2, sizeof(melody2)/sizeof(int)); break;
    case 3: playSong(melody3, noteDur3, sizeof(melody3)/sizeof(int)); break;
    case 4: playSong(melody4, noteDur4, sizeof(melody4)/sizeof(int)); break;
  }
}

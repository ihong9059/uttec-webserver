// melody.cpp
#include "melody.h"
#include "notes.h"

static const int PIN_BEEPER = 14; // LOW에서 삑
static const int PIN_SPK    = 33; // tone() 출력

void initMelody(){
  pinMode(PIN_BEEPER, OUTPUT);
  digitalWrite(PIN_BEEPER, HIGH); // 기본 OFF
  pinMode(PIN_SPK, OUTPUT);
  noTone(PIN_SPK);
}

void alarmBeep(){
  digitalWrite(PIN_BEEPER, LOW);
  delay(500);
  digitalWrite(PIN_BEEPER, HIGH);
}

// 간단 멜로디 4종
static void melody1(){
  int m[][2]={{NOTE_C4,200},{NOTE_D4,200},{NOTE_E4,200},{NOTE_F4,200},{NOTE_G4,400}};
  for(auto &p:m){ tone(PIN_SPK,p[0],p[1]); delay(p[1]+30); }
  noTone(PIN_SPK);
}
static void melody2(){
  int m[][2]={{NOTE_E4,200},{NOTE_G4,200},{NOTE_C5,300},{NOTE_B4,200},{NOTE_A4,400}};
  for(auto &p:m){ tone(PIN_SPK,p[0],p[1]); delay(p[1]+30); }
  noTone(PIN_SPK);
}
static void melody3(){
  int m[][2]={{NOTE_C5,180},{NOTE_D5,180},{NOTE_E5,180},{NOTE_G5,300},{NOTE_E5,300}};
  for(auto &p:m){ tone(PIN_SPK,p[0],p[1]); delay(p[1]+30); }
  noTone(PIN_SPK);
}
static void melody4(){
  int m[][2]={{NOTE_G4,200},{NOTE_A4,200},{NOTE_B4,200},{NOTE_C5,300},{NOTE_D5,400}};
  for(auto &p:m){ tone(PIN_SPK,p[0],p[1]); delay(p[1]+30); }
  noTone(PIN_SPK);
}

void playMelody(int no){
  switch(no){
    case 1: melody1(); break;
    case 2: melody2(); break;
    case 3: melody3(); break;
    case 4: melody4(); break;
    default: melody1(); break;
  }
}

#include "melody.h"
#include "notes.h"

static uint8_t pinBeep=14, pinSpk=33; static bool beepActiveLow=true;

void melodyBegin(uint8_t bp, uint8_t sp, bool al){
  pinBeep=bp; pinSpk=sp; beepActiveLow=al;
  pinMode(pinBeep, OUTPUT);
  digitalWrite(pinBeep, beepActiveLow? HIGH:LOW); // 대기=OFF
}

void beepOnce(uint16_t ms){
  digitalWrite(pinBeep, beepActiveLow? LOW:HIGH);
  delay(ms);
  digitalWrite(pinBeep, beepActiveLow? HIGH:LOW);
}

// 간단 멜로디들
static const int m1_notes[] = {NOTE_C4,NOTE_C4,NOTE_G4,NOTE_G4,NOTE_A4,NOTE_A4,NOTE_G4, REST};
static const int m1_durs [] = {4,4,4,4,4,4,2,4};

static const int m2_notes[] = {NOTE_G4,NOTE_G4,NOTE_A4,NOTE_A4,NOTE_G4,NOTE_G4,NOTE_E4, REST};
static const int m2_durs [] = {4,4,4,4,4,4,2,4};

static const int m3_notes[] = {NOTE_C4,NOTE_D4,NOTE_E4,NOTE_C4,NOTE_E4,NOTE_F4,NOTE_G4, REST};
static const int m3_durs [] = {4,4,4,4,4,4,2,4};

static const int m4_notes[] = {NOTE_C4,NOTE_F4,NOTE_G4,NOTE_C5, REST};
static const int m4_durs []  = {4,4,4,2,4};

static void play(const int* n, const int* d, int len){
  for(int i=0;i<len;i++){
    int dur = 1000 / d[i];
    if(n[i]==REST){ noTone(pinSpk); }
    else { tone(pinSpk, n[i], dur); }
    delay(dur * 1.3);
  }
  noTone(pinSpk);
}

void playMelodyId(int id){
  switch(id){
    case 1: play(m1_notes, m1_durs, sizeof(m1_notes)/sizeof(int)); break;
    case 2: play(m2_notes, m2_durs, sizeof(m2_notes)/sizeof(int)); break;
    case 3: play(m3_notes, m3_durs, sizeof(m3_notes)/sizeof(int)); break;
    default: play(m4_notes, m4_durs, sizeof(m4_notes)/sizeof(int)); break;
  }
}

#ifndef MELODY_H
#define MELODY_H

#include <Arduino.h>
#include "note.h"

void setupMelody(uint8_t pin, uint8_t redPin, uint8_t yellowPin, uint8_t bluePin);
void playMelody(int melody[], int noteDurations[], int length);

#endif

#include "switch.h"
static uint8_t swPin=32; static bool usePullup=true;
void switchBegin(uint8_t pin, bool pullup){ swPin=pin; usePullup=pullup; pinMode(swPin, pullup?INPUT_PULLUP:INPUT); }
bool switchPressed(){ int v=digitalRead(swPin); return usePullup? (v==LOW):(v==HIGH); }

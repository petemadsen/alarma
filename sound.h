#ifndef SOUND_H
#define SOUND_H

#include "common.h"
#include "pitches.h"

void beep()
{
  tone(tonePin, NOTE_A1);
  delay (250);
  noTone(tonePin);
}



#endif

#ifndef SOUND_H
#define SOUND_H



bool sound_play_next_note();

#ifdef USE_SOUND
unsigned long snd_last_access = 0;


// notes in the melody, // note durations: 4 = quarter note, 8 = eighth note, etc.
const int melody_enter[] PROGMEM = {
  NOTE_C4, 4, NOTE_G3, 8, NOTE_G3, 8, NOTE_A3, 4, NOTE_G3, 4, 0, 4, NOTE_B3, 4, NOTE_C4, 4, -1};
const int melody_brother_jakob[] PROGMEM = {
  NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4, NOTE_C4, 4,
  NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4, NOTE_C4, 4,
  NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 2,
  NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 2,
  NOTE_G4, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 2, NOTE_C4, 2,
  NOTE_G4, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 2, NOTE_C4, 2,
  NOTE_C4, 2, NOTE_A3, 2, NOTE_C4, 1,
  NOTE_C4, 2, NOTE_A3, 2, NOTE_C4, 1,
  -1};
const int melody_happy_birthday[] PROGMEM = {
  NOTE_G4, 4, NOTE_G4, 4, NOTE_A4, 2, NOTE_G4, 2, NOTE_C5, 2, NOTE_B4, 1,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_A4, 2, NOTE_G4, 2, NOTE_D5, 2, NOTE_C5, 1,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_G5, 2, NOTE_E5, 2, NOTE_C5, 2, NOTE_B4, 2, NOTE_A4, 2,
  NOTE_F5, 4, NOTE_F5, 4, NOTE_E5, 2, NOTE_C5, 2, NOTE_D5, 2, NOTE_C5, 1,
  -1
};
const int melody_beep[] PROGMEM = {
  NOTE_A1, 4,
  -1
};
const int melody_alarm[] PROGMEM = {
  NOTE_A2, 1, NOTE_A3, 1,
  -1
};

#define NR_MELODIES 5
#define MELODY_ALARM 3

const int* melodies[] = {
  melody_enter,
  melody_brother_jakob,
  melody_happy_birthday,
  melody_alarm,
  melody_beep
};



//int sound_play_this_melody = 0;
int* melody = 0;
int thisNote = 0;


#include "common.h"
#include "pitches.h"



void sound_setup()
{
  pinMode(tonePin, OUTPUT);
  Serial.println(F("[ok] sound"));
}



void play_melody();

void sound_beep()
{
  melody = 0;
  thisNote = 0;
  Serial.println(F("[snd] beep"));
  tone(tonePin, NOTE_A1);
  delay(250);
  noTone(tonePin);
}



void sound_loop()
{
  unsigned long m = millis();
  if((unsigned long)(m - snd_last_access) < 5) {
    return;
  }
  snd_last_access = m;

  if(!melody)
    return;

  if(!sound_play_next_note()) {
    // done
    melody = 0;
  }
  
  /*
  if((m - snd_last_access) > 15) {
    Serial.print("BAD");
    Serial.println(m - snd_last_access);
  }
  */

  
}


bool sound_melody(unsigned char snd)
{
  if(snd < NR_MELODIES) {
    melody = melodies[snd];
    thisNote = 0;

    Serial.print(F("[snd] playing "));
    Serial.println(snd);

    return true;
  }

  return false;
}


bool sound_play_next_note()
{
  int note = pgm_read_word(melody + thisNote);
  if(note == -1) {
    return false;
  }
  int note_duration = pgm_read_word(melody + thisNote + 1);
    
  // to calculate the note duration, take one second 
  // divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int noteDuration = 1000/note_duration;
  tone(tonePin, note, noteDuration);

  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pauseBetweenNotes = noteDuration * 1.30;
  Serial.println(pauseBetweenNotes);
  delay(pauseBetweenNotes);
  // stop the tone playing:
  noTone(tonePin);

  // next note
  thisNote += 2;

  return true;
}


void sound_off()
{
  melody = 0;
  noTone(tonePin);
}


#else
#define MELODY_ALARM 3

void sound_setup() {}
void sound_loop() {}
void sound_beep() {}
bool sound_melody(unsigned char /*snd*/) { return true; }
void sound_off() {}
#endif




#endif

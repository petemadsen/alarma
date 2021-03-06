#ifndef SOUND_H
#define SOUND_H



bool sound_play_next_note();

#ifdef USE_SOUND
unsigned long snd_last_access = 0;
unsigned long snd_delay = 100; // this is set according to current note/pause
bool snd_enabled = false;


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
const int melody_heilige_nacht[] PROGMEM = {
  NOTE_G4, 1, NOTE_F4, 1, NOTE_G4, 1, NOTE_E4, 1,
  NOTE_G4, 1, NOTE_F4, 1, NOTE_G4, 1, NOTE_E4, 1,
  -1
};

#define NR_MELODIES 6
#define MELODY_ALARM 3

const int* melodies[] = {
  melody_enter,
  melody_brother_jakob,
  melody_happy_birthday,
  melody_heilige_nacht,
  melody_alarm,
  melody_beep
};



//int sound_play_this_melody = 0;
int* melody = 0;
int thisNote = 0;


#include "common.h"
#include "pitches.h"



void sound_setup(bool enabled)
{
  snd_enabled = enabled;
  
  pinMode(tonePin, OUTPUT);
  Serial.println(F("[ok] sound"));
}



void play_melody();

void sound_beep()
{
  if(!snd_enabled)
    return;
    
  melody = 0;
  thisNote = 0;
  Serial.println(F("[snd] beep"));
  tone(tonePin, NOTE_A1);
  delay(250);
  noTone(tonePin);
}



void sound_loop()
{
  if(!snd_enabled)
    return;
    
  unsigned long m = millis();
  if((unsigned long)(m - snd_last_access) < snd_delay) {
    return;
  }
  snd_last_access = m;

  if(!melody)
    return;

  if(!sound_play_next_note())
  {
    // done
    melody = 0;
    snd_delay = 100;
    noTone(tonePin);
  }
  
  /*
  if((m - snd_last_access) > 15) {
    Serial.print("BAD");
    Serial.println(m - snd_last_access);
  }
  */
}


bool sound_melody(unsigned char snd);
void sound_play_debug(unsigned char snd)
{
  if(!sound_melody(snd))
    return;
  while(sound_play_next_note())
  {
  }
  // done
  melody = 0;
  snd_delay = 100;
  noTone(tonePin);
}


bool sound_melody(unsigned char snd)
{
  if(snd < NR_MELODIES)
  {
    int* next = melodies[snd];
    if(next == melody)
      return true;
   
    melody = next;
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

  // calculate the start of the next note
  snd_delay = noteDuration * 1.30;

#if 0
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
#endif

  // next note
  thisNote += 2;

  return true;
}


void sound_off()
{
  melody = 0;
  noTone(tonePin);
}


void sound_enable(bool b)
{
  snd_enabled = b;
  if(!snd_enabled)
    sound_off();
}


bool sound_is_enabled()
{
  return snd_enabled;
}


#else
#define MELODY_ALARM 3

void sound_setup(bool /*enabled*/) {}
void sound_loop() {}
void sound_beep() {}
bool sound_melody(unsigned char /*snd*/) { return true; }
void sound_off() {}
void sound_enable(bool) {}
void sound_is_enabled() { return false; }
#endif




#endif

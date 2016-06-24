#ifndef SOUND_H
#define SOUND_H





// notes in the melody, // note durations: 4 = quarter note, 8 = eighth note, etc.
const unsigned short melody_enter[] PROGMEM = {
  NOTE_C4, 4, NOTE_G3, 8, NOTE_G3, 8, NOTE_A3, 4, NOTE_G3, 4, 0, 4, NOTE_B3, 4, NOTE_C4, 4, -1};
const unsigned short melody_brother_jakob[] PROGMEM = {
  NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4, NOTE_C4, 4,
  NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4, NOTE_C4, 4,
  NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 2,
  NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 2,
  NOTE_G4, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 2, NOTE_C4, 2,
  NOTE_G4, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 2, NOTE_C4, 2,
  NOTE_C4, 2, NOTE_A3, 2, NOTE_C4, 1,
  NOTE_C4, 2, NOTE_A3, 2, NOTE_C4, 1,
  -1};
const unsigned short melody_happy_birthday[] PROGMEM = {
  NOTE_G4, 4, NOTE_G4, 4, NOTE_A4, 2, NOTE_G4, 2, NOTE_C5, 2, NOTE_B4, 1,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_A4, 2, NOTE_G4, 2, NOTE_D5, 2, NOTE_C5, 1,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_G5, 2, NOTE_E5, 2, NOTE_C5, 2, NOTE_B4, 2, NOTE_A4, 2,
  NOTE_F5, 4, NOTE_F5, 4, NOTE_E5, 2, NOTE_C5, 2, NOTE_D5, 2, NOTE_C5, 1,
  -1
};

#define NR_MELODIES 3
unsigned char sound_next_melody = NR_MELODIES;  // which sound to play

const unsigned short* melodies[] = {
  melody_enter,
  melody_brother_jakob,
  melody_happy_birthday
};



#include "common.h"
#include "pitches.h"

void play_melody();

void sound_beep()
{
  Serial.println(F("[snd] beep"));
  tone(tonePin, NOTE_A1);
  delay(250);
  noTone(tonePin);
}




void sound_setup()
{
  pinMode(tonePin, OUTPUT);
  sound_beep();
  
  Serial.println(F("[ok] sound"));
}




bool sound_melody(unsigned char snd)
{
  if(snd >= NR_MELODIES) {
    return false;
  }
  
  int thisNote = 0;
  const unsigned short* notes = melodies[snd];

  Serial.print(F("[snd] playing "));
  Serial.println(snd);

  // iterate over the notes of the melody:
  while (notes[thisNote] != -1) {
    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/notes[thisNote+1];
    tone(tonePin, notes[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(tonePin);

    // next note
    thisNote += 2;
  }

  return true;
}





void sound_alarm()
{
  //digitalWrite(ledPin, HIGH);

  tone(tonePin, NOTE_A2);
  delay (500);
  
  //digitalWrite(ledPin, LOW);
  
  tone(tonePin, NOTE_A3);
  delay (500);
}




#endif

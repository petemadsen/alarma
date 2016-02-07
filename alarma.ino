#include "pitches.h"
#include "sonic.h"
#include "sound.h"
#include "button.h"



// notes in the melody, // note durations: 4 = quarter note, 8 = eighth note, etc.
int melody_enter[] = {
  NOTE_C4, 4, NOTE_G3, 8, NOTE_G3, 8, NOTE_A3, 4, NOTE_G3, 4, 0, 4, NOTE_B3, 4, NOTE_C4, 4, -1};
int melody_brother_jakob[] = {
  NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4, NOTE_C4, 4,
  NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4, NOTE_C4, 4,
  NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 2,
  NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 2,
  NOTE_G4, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 2, NOTE_C4, 2,
  NOTE_G4, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_E4, 2, NOTE_C4, 2,
  NOTE_C4, 2, NOTE_A3, 2, NOTE_C4, 1,
  NOTE_C4, 2, NOTE_A3, 2, NOTE_C4, 1,
  -1};
int melody_happy_birthday[] = {
  NOTE_G4, 4, NOTE_G4, 4, NOTE_A4, 2, NOTE_G4, 2, NOTE_C5, 2, NOTE_B4, 1,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_A4, 2, NOTE_G4, 2, NOTE_D5, 2, NOTE_C5, 1,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_G5, 2, NOTE_E5, 2, NOTE_C5, 2, NOTE_B4, 2, NOTE_A4, 2,
  NOTE_F5, 4, NOTE_F5, 4, NOTE_E5, 2, NOTE_C5, 2, NOTE_D5, 2, NOTE_C5, 1,
  -1
};
int melody_alle_meine_entchen[] = {
  NOTE_C4, 4, NOTE_D4, 4, NOTE_E4, 4, NOTE_F4, 4, NOTE_G4, 2, NOTE_B4, 2,
  
  NOTE_B4, 4, NOTE_B4, 4, NOTE_B4, 4, NOTE_GS4, 4, NOTE_B4, 1,
  
   NOTE_B4, 4,NOTE_B4, 4,NOTE_GS4, 4,NOTE_F4, 4,   NOTE_F4, 1,
  
  NOTE_F4, 4,NOTE_E4, 4,NOTE_E4, 4,NOTE_G4, 4,NOTE_G4, 2,NOTE_G4, 2,
NOTE_G4, 4,NOTE_C4, 4,
  -1
};

#define NR_MELODIES 4
int* melodies[] = {
  melody_enter,
  melody_brother_jakob,
  melody_happy_birthday,
  melody_alle_meine_entchen
};





int modeBtnState = 0;

int snd = 3;// NR_MELODIES;  // which sound to play


int alarm_is_on = 0;



void play_melody() {
  int thisNote = 0;
  int* notes = melodies[snd%NR_MELODIES];

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
}


void alarm_on() {
  alarm_is_on = 1;
  Serial.println("ALARM");
}


void play_alarm() {
  digitalWrite(ledPin, LOW);

  tone(tonePin, NOTE_A2);
  delay (500);
  
  digitalWrite(ledPin, HIGH);
  
  tone(tonePin, NOTE_A3);
  delay (500);
}

void alarm_off() {
  alarm_is_on = 0;

  digitalWrite(ledPin, HIGH);

  noTone(tonePin);
}




void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(alarmPin, INPUT);
  pinMode(modePin, INPUT);

  Serial.begin (9600);
  Serial.println("INIT");
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //play_melody();
  sonic_calibrate();
  beep();
}


void loop() {
  /**
   * MODE
   */
  modeBtnState = digitalRead(modePin);
  if(modeBtnState == LOW) {
    Serial.println("button-pressed");
    // wait for release
    while(modeBtnState == LOW) {
      delay(50);
      modeBtnState = digitalRead(modePin);
    }

    if(alarm_is_on) {
      alarm_off();
      delay(5000);
    } 
    else {
      ++snd;
      play_melody();
    }
    return;
  }

  /**
   * ALARM
   */
  if(alarm_is_on) {
    play_alarm();
    return;
  }

  sonic_alarm();
  // button_alarm();
}











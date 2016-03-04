#include <Wire.h>

#include "pitches.h"
#include "sonic.h"
#include "sound.h"
#include "button.h"
#include "led.h"


int modeBtnState = 0;



int alarm_is_on = 0;


void alarm_on() {
  alarm_is_on = 1;
  Serial.println("ALARM");
}

void alarm_off() {
  alarm_is_on = 0;

  digitalWrite(ledPin, LOW);

  noTone(tonePin);
}





void setup() {
  Serial.begin (9600);
  Serial.println("Init..");

  Wire.begin();
  Wire.setClock(31L * 1000L);
  TWBR = 40;
  TWSR |= bit (TWPS0);
  TWSR |= bit (TWPS1);
  Serial.println("[ok] wire");

  return;

  pinMode(ledPin, OUTPUT);
  pinMode(alarmPin, INPUT);
  pinMode(modePin, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //play_melody();
  sonic_calibrate();
  beep();
}


void loop() {
  led_loop();
  return;
  
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











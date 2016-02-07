#include "common.h"

int alarmBtnState = 0;
int last_btn_state = 0;

void button_alarm()
{
  alarmBtnState = digitalRead(alarmPin);
  // debounce
  delay(100);
  if(digitalRead(alarmPin) != alarmBtnState) {
    return;
  }

  // state change
  if(alarmBtnState != last_btn_state) {
    if(alarmBtnState == HIGH) {
      digitalWrite(ledPin, HIGH);
      alarm_on();
    } 
    else {
      digitalWrite(ledPin, LOW);
      alarm_off();
    }

    last_btn_state = alarmBtnState;
  }


}


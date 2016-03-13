#include "common.h"
#include "i2c.h"


void buttons_setup()
{
}



int last_x = 0xff;
int buttons_loop()
{
  int x = read_i2c(I2C_PCF8574_3);
  if(last_x == x) {
    return -1;
  }

  last_x = x;
  
  if((x & BUTTON_1) == 0)
    return BUTTON_1;
  if((x & BUTTON_2) == 0)
    return BUTTON_2;
  if((x & BUTTON_3) == 0)
    return BUTTON_3;
    
  return -1;
}


#if 0
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
#endif


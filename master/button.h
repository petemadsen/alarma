#include "common.h"
#include "i2c.h"
#include "led.h"


bool button_clicked(uint8_t buttons, uint8_t mask);


void buttons_setup()
{
}


uint8_t button_is_pressed = 0;

int last_x = 0xff;
void buttons_loop()
{
  uint8_t x = read_i2c(I2C_PCF8574_3);
  if((last_x & BUTTON_MASK) == (x & BUTTON_MASK)) {
    return;
  }

  if(button_clicked(x, BUTTON_1_MASK)) {
    led_set_mode(LED_MODE_DISCO);
  } else if(button_clicked(x, BUTTON_2_MASK)) {
    led_set_mode(LED_MODE_FLASH);
  } else if(button_clicked(x, BUTTON_3_MASK)) {
    led_set_mode(LED_MODE_SONIC);
    led_all_off();
  }

  last_x = x;
}


bool button_clicked(uint8_t buttons, uint8_t mask)
{
  if((buttons & mask) == 0) {
    // remember is pressed
    button_is_pressed |= mask;
  } else if(button_is_pressed & mask) {
    button_is_pressed &= ~mask;
    return true;
  }

  return false;
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


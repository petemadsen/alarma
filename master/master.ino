#include <Wire.h>

#include "pitches.h"
#include "sonic.h"
#include "sound.h"
#include "button.h"
#include "led.h"
#include "oled.h"


int modeBtnState = 0;


int alarm_is_on = 0;


void alarm_on() {
  alarm_is_on = 1;
  Serial.println(F("ALARM"));
}

void alarm_off() {
  alarm_is_on = 0;

  //digitalWrite(ledPin, HIGH);

  //noTone(tonePin);
}





void setup()
{
  Serial.begin (9600);
  Serial.println(F("Init.."));

  Wire.begin();
  Wire.setClock(31L * 1000L);
  TWBR = 40;
  TWSR |= bit (TWPS0);
  TWSR |= bit (TWPS1);
  Serial.println(F("[ok] i2c"));

  led_setup();
  Serial.println(F("[ok] led"));

  //oled_setup();
#ifdef USE_OLED
  Serial.println(F("[ok] oled"));
  oled_setup();
#endif

  buttons_setup();
  Serial.println(F("[ok] buttons"));

#ifdef USE_RFID
  rfid_init();
  Serial.println(F("[ok] rfid"));
#endif

  //mp3_setup();
  //Serial.println(F("[ok] mp3"));

  sound_setup();

  bt_setup();

  //play_melody();
  sonic_calibrate();
  sound_beep();

  //led_disco();
  led_all_off();

  //pinMode(ledPin, OUTPUT);
  //
  //pinMode(modePin, INPUT);



  Serial.println(F("[OK] INIT"));
}


int mode = MODE_LED_ACTION;
int mode_oled = MODE_STOP;


#if 0
#define CHECK_BUTTONS() if(handle_buttons()) return;
bool handle_buttons()
{
  int button = buttons_loop();
  if(button == -1) {
    return false;
  }
  
  Serial.print("b:");
  Serial.println(button);
  switch(button) {
  case BUTTON_1:
    if(mode == MODE_LED_ACTION) {
      mode = MODE_STOP;
      oled_set_text("Stopp");
    } else {
      mode = MODE_LED_ACTION;
      oled_set_text("Lauflicht");
    }
    break;

  case BUTTON_2:
    if(mode_oled == MODE_OLED_ON) {
      mode_oled = MODE_STOP;
    } else {
      mode_oled = MODE_OLED_ON;
    }
    break;

  case BUTTON_3:
    break;

  default:
    return false;
  }

  return true;
}
#endif


void loop()
{
  //CHECK_BUTTONS();


#if 0
  if(mode == MODE_LED_ACTION) {
    led_all_off();
    delay(1000);
    CHECK_BUTTONS();
    
    led_set(1, true, false, false);
    led_set(2, false, true, false);
    led_set(3, false, false, true);
    led_set(4, true, false, false);
    led_set(5, false, true, false);
    led_set(6, false, false, true);
    led_set(7, true, false, false);
    CHECK_BUTTONS();
    delay(1000);
    CHECK_BUTTONS();

    led_all_off();
    delay(1000);
    CHECK_BUTTONS();

    for(int i=1; i<=7; ++i) {
      CHECK_BUTTONS();
      led_set(i, true, false, false);
      delay(100);
      led_set(i, false, false, false);
    }
    for(int i=6; i>=2; --i) {
      CHECK_BUTTONS();
      led_set(i, true, false, false);
      delay(100);
      led_set(i, false, false, false);
    }
  }
#endif
  //led_loop();

  if(mode_oled == MODE_OLED_ON) {
    //oled_loop();
  }

#ifdef USE_RFID
  rfid_loop();
#endif
  
  
  /**
   * MODE
   *
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
  */

  /**
   * ALARM
   */
//  if(alarm_is_on) {
//    sonic_alarm();
//    return;
//  }

  //sonic_loop();
  // button_alarm();

  bt_loop();

}











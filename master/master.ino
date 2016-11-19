#include <Wire.h>

#include "pitches.h"
#include "sonic.h"
#include "sound.h"
#include "button.h"
#include "led.h"
#include "oled.h"
#include "mode.h"
#include "settings.h"
#include "cmd.h"


void setup()
{
  Serial.begin (9600);
  Serial.println(F("Init.."));

  settings_setup();

  Wire.begin();
#ifdef USE_SLOW_I2C
  Serial.println(F("[i2c] slow"));
  Wire.setClock(31L * 1000L);
  TWBR = 40;
  TWSR |= bit (TWPS0);
  TWSR |= bit (TWPS1);
#endif
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

  sound_setup(settings_has_sound());

  bt_setup();

  //play_melody();
  sonic_setup();

  //led_disco();
  led_all_off();

  mode_setup();

  menu_init();

  pinMode(CHRISTMAS_TREE, OUTPUT);

  Serial.println(F("[OK] INIT"));  
  sound_beep();
}


void christmas_tree(bool b)
{
  digitalWrite(CHRISTMAS_TREE, b ? HIGH : LOW);
}


void loop()
{
  bt_loop();

  buttons_loop();

  i2c_loop();

#ifdef USE_RFID
  rfid_loop();
#endif

  led_loop();

  sonic_loop();

  sound_loop();
  
  oled_loop();

  mode_loop();

  if(Serial.available())
  {
    cmd_add_char(Serial);
  }
}











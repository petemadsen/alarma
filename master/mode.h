void mode_set(unsigned char m);
void menu_up();
void menu_down();
void menu_click();
void menu_open();
void mode_sonic_draw(U8GLIB& display);


#define MODE_NONE 0
#define MODE_SONIC 1
unsigned char mode = MODE_NONE;


unsigned long mode_last_access = 0;
unsigned short mode_access_delay = 0;


void mode_setup()
{
  Serial.println("[ok] mode");
}


void mode_loop()
{
  if(mode_access_delay == 0)
    return;

  unsigned long m = millis();
    if((unsigned long)(m - mode_last_access) < mode_access_delay) {
    return;
  }
  mode_last_access = m;

  switch(mode) {
  case MODE_SONIC:
    break;
  }
}


void mode_rotary_click()
{
  switch(mode) {
  case MODE_SONIC:
    mode_set(MODE_NONE);
    break;
  default:
    menu_click();
    break;
  }
}


void mode_rotary_up()
{
  switch(mode) {
  case MODE_SONIC:
    sonic_alarm_add(-10);
    break;
  default:
    menu_up();
    break;
  }
}



void mode_rotary_down()
{
  switch(mode) {
  case MODE_SONIC:
    sonic_alarm_add(+10);
    break;
  default:
    menu_down();
    break;
  }
}


void mode_set(unsigned char m)
{
  mode = m;
  
  switch(mode) {
  case MODE_SONIC:
    mode_access_delay = 100;
    oled_set_draw_function(mode_sonic_draw);
    break;
  default:
    menu_open();
  }
}


void mode_sonic_draw(U8GLIB& display)
{
  int d = sonic_get_last_distance();
  char buf[12];

  int a = sonic_get_alarm_distance();
  
  sprintf(buf, "> %d cm", d);
  //d.drawStr(0, d.getFontAscent(), buf);
  //Serial.println(buf);
  display.drawStr(0, 20, buf);

  sprintf(buf, "@ %d cm", a);
  display.drawStr(0, 60, buf);

  if(a != -1 and d < a)
  {
    led_set_mode(LED_MODE_FLASH);
    sound_melody(MELODY_ALARM);
    display.drawStr(80, 20, "ALARM");
  }
  else
  {
    sound_off();
  }
}
void led_sonic_step()
{
}


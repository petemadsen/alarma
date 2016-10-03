#ifndef MY_MENU_H
#define MY_MENU_H


#define MENU_NR_ITEMS 8
#define MENU_DISPLAY_ITEMS 5


unsigned char menu_item = MENU_NR_ITEMS; // current menu item, MENU_NR_ITEMS=off
unsigned char menu_display_top = 0;


#define MENU_SONIC 2
#define MENU_SOUND 7
const char* const menu0 PROGMEM = "Disco";
const char* const menu1 PROGMEM = "Flash";
const char* const menu2 PROGMEM = "Sonic";
const char* const menu3 PROGMEM = "Melody0";
const char* const menu4 PROGMEM = "Melody1";
const char* const menu5 PROGMEM = "Melody2";
const char* const menu6 PROGMEM = "Melody Alarm";
const char* const menu7 PROGMEM = "Sound";

const char* const menu_items[] = {menu0, menu1, menu2, menu3, menu4, menu5, menu6, menu7};


void menu_init()
{
  //oled_set_draw_function(menu_draw);
}


void menu_up()
{
  if(menu_item == MENU_NR_ITEMS)
    return;

  if(menu_item != 0) {
    --menu_item;
    if(menu_item < menu_display_top)
      --menu_display_top;
    oled_set_draw_function(menu_draw);
  }
}


void menu_down()
{
  if(menu_item == MENU_NR_ITEMS)
    return;
 
  if((menu_item+1) < MENU_NR_ITEMS) {
    ++menu_item;
    if(menu_item >= (menu_display_top+MENU_DISPLAY_ITEMS))
        ++menu_display_top;
    oled_set_draw_function(menu_draw);
  }
}


void menu_open()
{
  if(menu_item ==MENU_NR_ITEMS) {
    menu_item = 0;
  }
  oled_set_draw_function(menu_draw);
}


void menu_click()
{
  sound_beep();
  
  if(menu_item ==MENU_NR_ITEMS) {
    menu_item = 0;
    oled_set_draw_function(menu_draw);
    return;
  }
  
  switch(menu_item) {
    case 0:
      led_set_mode(LED_MODE_DISCO);
      oled_set_draw_function(menu_draw);
      break;
    case 1:
      led_set_mode(LED_MODE_FLASH);
      oled_set_draw_function(menu_draw);
      break;
    case MENU_SONIC:
      mode_set(MODE_SONIC);
      break;
    case 3:
    case 4:
    case 5:
    case 6:
      sound_melody(menu_item - 3);
      break;
    case MENU_SOUND:
      mode_set(MODE_SOUND);
      break;
    break;
  }
}


void menu_draw(U8GLIB& d)
{
  // const char* const strings[], unsigned char current, unsigned char from, unsigned char num2display
  // menu_items, menu_item, menu_display_top, MENU_DISPLAY_ITEMS

  u8g_uint_t y = d.getFontAscent();
  
  for(unsigned char i=menu_display_top; i<menu_display_top+MENU_DISPLAY_ITEMS; ++i) {
    d.drawStr(0, y, i==menu_item ? F("> ") : F(". "));
    d.drawStr(20, y, menu_items[i]);
    y += d.getFontAscent();
  }
}



#endif

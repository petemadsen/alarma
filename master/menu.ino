#ifndef MY_MENU_H
#define MY_MENU_H


#define MENU_NR_ITEMS 3
#define MENU_DISPLAY_ITEMS 3


unsigned char menu_item = MENU_NR_ITEMS; // off


const char* const menu0 PROGMEM = "Disco";
const char* const menu1 PROGMEM = "Flash";
const char* const menu2 PROGMEM = "OFF";

const char* const menu_items[] = {menu0, menu1, menu2};

void menu_up()
{
  if(menu_item == MENU_NR_ITEMS)
    return;
    
  if(menu_item != 0) {
    --menu_item;
    menu_update();
  }
}


void menu_down()
{
  if(menu_item == MENU_NR_ITEMS)
    return;
    
  if((menu_item+1) < MENU_NR_ITEMS) {
    ++menu_item;
    menu_update();
  }
}


void menu_click()
{
  sound_beep();
  
  if(menu_item ==MENU_NR_ITEMS) {
    menu_item = 0;
  } else {
    switch(menu_item) {
      case 0:
        led_set_mode(LED_MODE_DISCO);
        break;
      case 1:
        led_set_mode(LED_MODE_FLASH);
        break;
      case 2:
        led_set_mode(LED_MODE_SONIC);
        led_all_off();
      break;
    }
  }
  
  menu_update();
}

void menu_update()
{
  oled_set_menu(menu_items, menu_item, MENU_DISPLAY_ITEMS);
}


#endif

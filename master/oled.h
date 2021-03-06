#ifndef MY_OLED_H
#define MY_OLED_H


#ifdef USE_OLED
#include "U8glib.h"

#define OLED_RESET 4
unsigned long oled_last_access = 0;


U8GLIB_SSD1306_128X64 display(U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_DEV_0);  // I2C / TWI

typedef void (*oled_draw_func_p)(U8GLIB&);
oled_draw_func_p oled_draw_func = 0;


void oled_setup()
{
#if 0
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, I2C_OLED);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  display.setTextSize(2);
  display.setTextColor(WHITE);
#endif

  // flip screen, if required
  // display.setRot180();
  
  // set SPI backup if required
  //display.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if ( display.getMode() == U8G_MODE_R3G3B2 ) {
    display.setColorIndex(255);     // white
  }
  else if ( display.getMode() == U8G_MODE_GRAY2BIT ) {
    display.setColorIndex(3);         // max intensity
  }
  else if ( display.getMode() == U8G_MODE_BW ) {
    display.setColorIndex(1);         // pixel on
  }
  else if ( display.getMode() == U8G_MODE_HICOLOR ) {
    display.setHiColorByRGB(255,255,255);
  }
}


void oled_loop()
{
  unsigned long m = millis();
    if((unsigned long)(m - oled_last_access) < 100) {
    return;
  }
  oled_last_access = m;

  // picture loop
  display.firstPage();  
  do {
    if(oled_draw_func) {
      oled_draw_func(display);
    } else {
      display.setFont(u8g_font_unifont);
      display.drawStr(0, 20, "Druecken bitte!");
    }
  } while( display.nextPage() );
}


void oled_set_draw_function(oled_draw_func_p f)
{
  oled_draw_func = f;
}



#else // USE_OLED

void oled_set_menu(const char* const strings[], unsigned char current, unsigned char max_nums, unsigned char num2display) {}
void oled_set_draw_function(oled_draw_func_p f) {}

#endif // USE_OLED

#endif // MY_OLED_H

/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
#ifndef MY_OLED_H
#define MY_OLED_H


#ifdef USE_OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


void oled_set_text(const char* text)
{
  display.setCursor(0,0);
  display.clearDisplay();
  display.println(text);
  display.display();
}

void oled_set_flash_text(const __FlashStringHelper* text)
{
  display.setCursor(0,0);
  display.clearDisplay();
  display.println(text);
  display.display();
}

void oled_set_menu(const char* const strings[], unsigned char current, unsigned char from, unsigned char num2display)
{
  display.setCursor(0, 0);
  display.clearDisplay();
  for(unsigned char i=from; i<from+num2display; ++i) {
    display.print(i==current ? F("> ") : F(". "));
    display.println(strings[i]);
  }
  display.display();
}

void oled_set_num(long d)
{
  display.setCursor(0,0);
  display.clearDisplay();
  display.println(d);
  display.display();
}

void oled_setup()
{
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
}

void oled_loop()
{
#if 0
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println(F("Hallo\nMax!"));
  display.display();
  delay(1);
 
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);    
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
#endif
}

#else // USE_OLED

void oled_set_menu(const char* const strings[], unsigned char current, unsigned char max_nums, unsigned char num2display) {}
void oled_set_flash_text(const __FlashStringHelper* text) {}
void oled_set_text(const char* text) {}
void oled_set_num(long d) {}

#endif // USE_OLED

#endif // MY_OLED_H

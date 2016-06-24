#ifndef ALARMA_LED_H
#define ALARMA_LED_H

#include "i2c.h"


void led_disco_init();
void led_disco_step();


#define LED_MODE_NONE 0
#define LED_MODE_DISCO 1
uint8_t led_mode = LED_MODE_NONE;
unsigned long led_last_access = 0;


// each mode can have its own variables/data
uint8_t led_disco_steps = 0;


uint8_t led_state[3] = { 0xff, 0xff, 0xff };


void led_all_off()
{
  led_state[0] = led_state[1] = led_state[2] = 0xff;
  send_cmd(I2C_PCF8574_1, 0xff);
  send_cmd(I2C_PCF8574_2, 0xff);
  send_cmd(I2C_PCF8574_3, 0xff);
}


void led_setup()
{
  led_all_off();
}


void led_loop()
{
  switch(led_mode) {
    case LED_MODE_DISCO:
      led_disco_step();
      break;
  }
}


void led_set_mode(uint8_t mode)
{
  Serial.print(F("[led] set-mode "));
  Serial.println(mode);
  
  led_mode = mode;
  switch(led_mode) {
    case LED_MODE_DISCO:
      led_disco_init();
      break;
  }
}

void led_loop_obsolete()
{
  //read_i2c(I2C_PCF8574);
  
//  send_cmd(I2C_PCF8574, 0x0);
//  delay(1 * 1000);
//  send_cmd(I2C_PCF8574, 0xff);
//  delay(1 * 1000);

  send_cmd(I2C_PCF8574_1, 0xff);
  delay(500);
  
  int x = 0x80;
  for(int i=0; i<6; ++i) {
    send_cmd(I2C_PCF8574_1, ~x);
    delay(500);
    x >>= 1;
  }

  send_cmd(I2C_PCF8574_1, 0xff);
  delay(500);

  x = 0x90;
  for(int i=0; i<3; ++i) {
    send_cmd(I2C_PCF8574_1, ~x);
    delay(500);
    x >>= 1;
  }

  send_cmd(I2C_PCF8574_1, 0xff);
  delay(500);

  for(int i=0; i<8; ++i) {
    send_cmd(I2C_PCF8574_1, ~(i<<5));
    delay(500);
  }
}


void led_set(uint8_t num, bool red, bool green, bool blue)
{
  if(num==0 || num > 7)
    return;

  if(num==1) {
    led_state[0] |= (7 << 5);
    if(red)
      led_state[0] &= ~0x80;
    if(green)
      led_state[0] &= ~0x40;
    if(blue)
      led_state[0] &= ~0x20;
      
  } else if(num==2) {
    led_state[0] |= (7 << 2);
    if(red)
      led_state[0] &= ~0x10;
    if(green)
      led_state[0] &= ~0x08; // swapped
    if(blue)
      led_state[0] &= ~0x04; // swapped
      
  } else if(num==3) {
    led_state[0] |= (3 << 0);
    if(red)
      led_state[0] &= ~0x02;
    if(green)
      led_state[0] &= ~0x01;
    led_state[1] |= (1 << 7);
    if(blue)
      led_state[1] &= ~0x80;
      
  } else if(num==4) {
    led_state[1] |= (7 << 4);
     if(red)
      led_state[1] &= ~0x40;
    if(green)
      led_state[1] &= ~0x20;
     if(blue)
      led_state[1] &= ~0x10;
      
  } else if(num==5) {
    led_state[1] |= (7 << 1);
     if(red)
      led_state[1] &= ~0x08;
    if(green)
      led_state[1] &= ~0x04;
     if(blue)
      led_state[1] &= ~0x02;
      
  } else if(num==6) {
    led_state[1] |= (1 << 0);
    if(red)
      led_state[1] &= ~0x01;
    led_state[2] |= (3 << 6);
    if(green)
      led_state[2] &= ~0x80;
    if(blue)
      led_state[2] &= ~0x40;
      
  } else if(num==7) {
    led_state[2] |= (7 << 3);
     if(red)
      led_state[2] &= ~0x20;
    if(green)
      led_state[2] &= ~0x10;
     if(blue)
      led_state[2] &= ~0x08;
  }

  // make sure that buttons are HIGH
  led_state[2] |= BUTTON_MASK;

  send_cmd(I2C_PCF8574_1, led_state[0]);
  send_cmd(I2C_PCF8574_2, led_state[1]);
  send_cmd(I2C_PCF8574_3, led_state[2]);
}


void led_set_all(bool red, bool green, bool blue)
{
  for(int i=0; i<8; ++i) {
    led_set(i, red, green, blue);
  }
}



void led_disco_init()
{
  led_disco_steps = 100;
}

void led_disco_step()
{
  unsigned long m = millis();
  if((unsigned long)(m - led_last_access) < 250) {
    return;
  }
    
  led_state[0] = m & 0xff;
  led_state[1] = (m >> 8) & 0xff;
  led_state[2] = (m >> 16) & 0xff;

  if((led_disco_steps%2)) {
    led_state[0] = ~led_state[0];
    led_state[1] = ~led_state[1];
    led_state[2] = ~led_state[2];
  }

  // make sure that buttons are HIGH
  led_state[2] |= BUTTON_MASK;
  
  send_cmd(I2C_PCF8574_1, led_state[0]);
  send_cmd(I2C_PCF8574_2, led_state[1]);
  send_cmd(I2C_PCF8574_3, led_state[2]);

  led_last_access = m;
  if(--led_disco_steps == 0) {
    led_set_mode(LED_MODE_NONE);
  }
}

#endif

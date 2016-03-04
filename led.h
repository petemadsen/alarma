#ifndef ALARMA_LED_H
#define ALARMA_LED_H

#include "i2c.h"

uint8_t led_state[3] = { 0xff, 0xff, 0xff };


void led_setup()
{
  send_cmd(I2C_PCF8574, 0xff);
}


void led_loop()
{
  //read_i2c(I2C_PCF8574);
  
//  send_cmd(I2C_PCF8574, 0x0);
//  delay(1 * 1000);
//  send_cmd(I2C_PCF8574, 0xff);
//  delay(1 * 1000);

  send_cmd(I2C_PCF8574, 0xff);
  delay(500);
  
  int x = 0x80;
  for(int i=0; i<6; ++i) {
    send_cmd(I2C_PCF8574, ~x);
    delay(500);
    x >>= 1;
  }

  send_cmd(I2C_PCF8574, 0xff);
  delay(500);

  x = 0x90;
  for(int i=0; i<3; ++i) {
    send_cmd(I2C_PCF8574, ~x);
    delay(500);
    x >>= 1;
  }

  send_cmd(I2C_PCF8574, 0xff);
  delay(500);

  for(int i=0; i<8; ++i) {
    send_cmd(I2C_PCF8574, ~(i<<5));
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
  }

  send_cmd(I2C_PCF8574, led_state[0]);
}

#endif

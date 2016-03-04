#include "i2c.h"


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


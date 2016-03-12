#ifndef COMMON_H
#define COMMON_H

//#define DEBUG

#define alarmPin 2 // digital
#define tonePin 9  // digital
#define ledPin 13   // on-board
#define modePin 5

#define echoPin 7 // Echo Pin
#define trigPin 6 // Trigger Pin

#define I2C_PCF8574_1 (0x40>>1)
#define I2C_PCF8574_2 (0x4e>>1)
#define I2C_PCF8574_3 (0x7e>>1)

#define I2C_OLED    (0x78>>1)

extern void alarm_on();

extern void alarm_off();

#endif

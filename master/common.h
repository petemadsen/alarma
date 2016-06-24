#ifndef COMMON_H
#define COMMON_H

//#define DEBUG

//#define alarmPin 2 // digital
#define tonePin 8  // digital
//#define ledPin 13   // on-board
//#define modePin 5

#define MP3_NEXT_PIN 3
#define MP3_PREV_PIN 2


#define BT_PIN_POWER 4
#define BT_PIN_TX 6
#define BT_PIN_RX 7
#define BT_BAUD 9600



// sonic
#define echoPin 10 // Echo Pin
#define trigPin 9 // Trigger Pin

#define I2C_PCF8574_1 (0x40>>1)
#define I2C_PCF8574_2 (0x4e>>1)
#define I2C_PCF8574_3 (0x7e>>1)

#define BUTTON_1 0x01
#define BUTTON_2 0x02
#define BUTTON_3 0x04

#define MODE_STOP 0
#define MODE_LED_ACTION 1
#define MODE_OLED_ON 2

#define I2C_OLED    (0x78>>1)

extern void alarm_on();

extern void alarm_off();

//#define USE_OLED
//#define USE_RFID

#endif
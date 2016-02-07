#ifndef COMMON_H
#define COMMON_H

//#define DEBUG

#define alarmPin 2 // digital
#define tonePin 9  // digital
#define ledPin 13   // on-board
#define modePin 5

#define echoPin 7 // Echo Pin
#define trigPin 6 // Trigger Pin

extern void alarm_on();

extern void alarm_off();

#endif

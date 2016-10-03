#include <Arduino.h>

#include "common.h"
#include "sound.h"


#define ALARM_MAX 1000 // Maximum range needed

int distance = 0; // last distance measured
int alarm_distance = -1;


int sonic_get_last_distance()
{
  return distance;
}


int sonic_get_alarm_distance()
{
  return alarm_distance;
}


void sonic_alarm_add(int add)
{
  alarm_distance += add;
  if(alarm_distance < 0)
    alarm_distance = -1;
  else if(alarm_distance > ALARM_MAX)
    alarm_distance = ALARM_MAX;
}


int sonic_measure_distance()
{
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5); 

  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH);
  if(duration == 0) {
    return ALARM_MAX;
  }

  // Calculate the distance (in cm) based on the speed of sound.
  unsigned long distance = duration/58.2;

  //Serial.println(distance);

  if(distance > ALARM_MAX) {
    return ALARM_MAX;
  }
  return distance;
}


void sonic_setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  alarm_distance = -1;
}


void sonic_calibrate_old()
{
  Serial.println(F("Calibrating..."));
  
  for(int i=0; i<10; ++i)
  {
    unsigned long d = sonic_measure_distance();
    
    Serial.print(F("step "));
    Serial.print(i);
    Serial.print(F(" | "));
    Serial.print(d);
    
    if(i==0) {
      alarm_distance = d;
    } 
    else {
      alarm_distance = (alarm_distance + d) / 2;
    }
    
    Serial.print(F(" | "));
    Serial.println(alarm_distance);
  }

  alarm_distance -= 10;

  if(alarm_distance > 300)
    alarm_distance = -1;

  Serial.print(F("calibrated at "));
  Serial.println(alarm_distance);
}


void sonic_loop()
{
  if(alarm_distance < 50) {
    //return;
  }
  
  distance = sonic_measure_distance();

  //Serial.println(distance);
  return;

#ifdef DEBUG
  Serial.println(d);
#endif
  if(distance!=0 && distance < alarm_distance) {
    Serial.print(F("detected"));
    Serial.println(distance);
    //alarm_on();
    sound_beep();
  }
}









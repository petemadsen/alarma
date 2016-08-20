#include <Arduino.h>

#include "common.h"
#include "sound.h"




long maxRange = 1000; // Maximum range needed
long minRange = 0; // Minimum range needed

long distance = 0; // last distance measured


long alarm_distance = -1;


long sonic_get_last_distance()
{
  return distance;
}


long sonic_measure_distance()
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
    return maxRange;
  }

  //Calculate the distance (in cm) based on the speed of sound.
  long distance = duration/58.2;

  //Serial.println(distance);

  if(distance < minRange) {
    return 0;
  }
  if(distance > maxRange) {
    return maxRange;
  }
  return distance;
}


void sonic_calibrate()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  alarm_distance = 0;

  Serial.println(F("Calibrating..."));
  
  for(int i=0; i<10; ++i) {
    long d = sonic_measure_distance();
    
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









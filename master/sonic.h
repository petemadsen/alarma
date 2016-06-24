#include <Arduino.h>

#include "sound.h"




int maxRange = 200; // Maximum range needed
int minRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance



long alarm_distance = -1;



long sonic_get_distance()
{
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;

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
    long d = sonic_get_distance();
    
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
  
  long d = sonic_get_distance();

  Serial.println(d);
  return;

#ifdef DEBUG
  Serial.println(d);
#endif
  if(d!=0 && d < alarm_distance) {
    Serial.print("detected");
    Serial.println(d);
    //alarm_on();
    sound_beep();
  }
}









#ifdef USE_RFID
#include <SPI.h>
#include "rfid-master/RFID.h"                                  // RFID Master2 Library

#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN);

// TODO: millis() wrap-around
#define ACCESS_DENIED    10000 // time in milli seconds
#define ACCESS_GRANTED   1000
unsigned long rfid_last_access = 0;
unsigned long rfid_current_interval = ACCESS_GRANTED;

#define KEY_LEN 4
#define NR_KEYS 2
unsigned char rfid_valid_keys[] = {
  0xd7, 0xa6, 0x67,0x11,
  0xd0, 0xc8, 0x33, 0x2a};


void rfid_init()
{
  // Serial,SPI und RFID starten
  SPI.begin();
 
  rfid.init();
}


void rfid_loop()
{
  if((unsigned long)(millis() - rfid_last_access) < rfid_current_interval)
  {
    return;
  }
  
  if(rfid.isCard() && rfid.readCardSerial())
  {
    rfid_last_access = millis();
    
    //Serial.print(millis());
    Serial.print("[ rfid] ");
    Serial.print(rfid.serNum[0], HEX);
    Serial.print("-");
    Serial.print(rfid.serNum[1], HEX);
    Serial.print("-");
    Serial.print(rfid.serNum[2], HEX);
    Serial.print("-");
    Serial.print(rfid.serNum[3], HEX);
    Serial.println();

    int key_id = 0;
    for(; key_id<NR_KEYS; ++key_id) {
      bool found = true;
      for(int k=0; k<KEY_LEN && found; ++k) {
        found = rfid_valid_keys[key_id*KEY_LEN + k] == rfid.serNum[k];
      }
      Serial.println(found ? "found" : "not");
      if(found) {
        break;
      }
    }

    bool found = key_id < NR_KEYS;
    bool r, g, b;

    switch(key_id) {
    case 0:
      oled_set_text("Hallo\nMax!");
      r = false; g = true; b = false;
      break;
    case 1:
      oled_set_text("Hallo\nArtur!");
      r = false; g = false; b = true;
      break;
    default:
      oled_set_text("Zugang\nverboten!\nAlarm!");
      r = true; g = false; b = false;
      break;
    }

    led_set_all(r, g, b);
    delay(1 * 250);
    led_set_all(false, false, false);
    delay(1 * 250);
    led_set_all(r, g, b);
    delay(1 * 250);
    oled_set_text("Bereit");
    led_set_all(false, false, false);
  }
  
  rfid.halt();
}
#endif

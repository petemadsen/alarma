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
#define NR_KEYS 1
unsigned char rfid_valid_keys[KEY_LEN*NR_KEYS];


void rfid_init()
{
  // Serial,SPI und RFID starten
  SPI.begin();
 
  rfid.init();

  rfid_valid_keys[0] = 0xd7;
  rfid_valid_keys[1] = 0xa6;
  rfid_valid_keys[2] = 0x67;
  rfid_valid_keys[3] = 0x11;
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

    bool found = true;
    for(int i=0; i<NR_KEYS; ++i) {
      found = true;
      for(int k=0; k<KEY_LEN && found; ++k) {
        Serial.print(rfid_valid_keys[i*KEY_LEN + k], HEX);
        Serial.print(rfid.serNum[k], HEX);
        Serial.println("--done");
        found = rfid_valid_keys[i*KEY_LEN + k] == rfid.serNum[k];
      }
      if(found) {
        break;
      }
    }
    oled_set_text(found ? "Hallo\nMax!" : "Zugang\nverboten!\nAlarm!");
    //Serial.println(found ? "Hallo\nMax!" : "Zugang\nverboten!\nAlarm!");
  }
  
  rfid.halt();
}

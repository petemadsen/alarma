#include <SoftwareSerial.h>
#include "common.h"


SoftwareSerial myBTSerial(BT_PIN_TX, BT_PIN_RX);



boolean enabled = false;

#define BT_TIMEOUT (1000L * 60)
unsigned long bt_last_access = 0;

void bt_setup()
{
  myBTSerial.begin(BT_BAUD);
  pinMode(BT_PIN_POWER, OUTPUT);
  bt_enable(true);

  Serial.println(F("[ok] BT"));
}


void bt_enable(boolean enable)
{
  enabled = enable;
  digitalWrite(BT_PIN_POWER, enable ? HIGH : LOW);
  bt_last_access = millis();
}


void bt_loop()
{
  if(!enabled) {
    return;
  }
  
  while (myBTSerial.available()) {
    bt_last_access = millis();

    Serial.print("bt-char: ");
    Serial.print(myBTSerial.read(), HEX);
    Serial.println();
    //cmd_add_char(myBTSerial);
  }
  
  //while(Serial.available()) {
  //  myBTSerial.write(Serial.read());
  //}
  
  // check timeout
  if((unsigned long)(millis() - bt_last_access) >= BT_TIMEOUT) {
    //rfid_bluetooth(false);
  }
}


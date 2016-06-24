#include <SoftwareSerial.h>
#include "common.h"


SoftwareSerial myBTSerial(BT_PIN_TX, BT_PIN_RX);


#define BT_CMD_HELP '?'
#define BT_CMD_LIGHTS 'L'
#define BT_CMD_BEEP 'B'
#define BT_CMD_MELODY 'M'
#define BT_CMD_STOP 'S'
#define BT_CMD_TEXT 'T'


#define MAX_BT_BUF_LEN 20
unsigned char bt_rcv_buffer[MAX_BT_BUF_LEN + 1];
unsigned char bt_rcv_buffer_cnt = 0;


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

    unsigned char ch = myBTSerial.read();

    if(ch < ' ' || ch > 'z') {
      if(bt_rcv_buffer_cnt != 0) {
        bt_rcv_buffer[bt_rcv_buffer_cnt] = 0;
        bool ok = bt_parse_command();
        bt_rcv_buffer_cnt = 0;
        myBTSerial.println(ok ? F("ok") : F("err"));
      }
    } else {
      if(bt_rcv_buffer_cnt < MAX_BT_BUF_LEN) {
        bt_rcv_buffer[bt_rcv_buffer_cnt++] = ch;
      }
    }

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


bool bt_parse_command()
{
  int int_param;
  
  switch(bt_rcv_buffer[0]) {
    case BT_CMD_LIGHTS:
      if(bt_rcv_buffer_cnt == 4) {
        bool r = (bt_rcv_buffer[1]=='1' ? true : false);
        bool g = (bt_rcv_buffer[2]=='1' ? true : false);
        bool b = (bt_rcv_buffer[3]=='1' ? true : false);
        led_set_all(r, g, b);
      }
      return true;
      
    case BT_CMD_BEEP:
      sound_beep();
      return true;
      
    case BT_CMD_MELODY:
      int_param = bt_parse_dec(1);
      if(int_param != -1) {
        return sound_melody(int_param);
      }
      return false;
      
    case BT_CMD_STOP:
      led_set_all(false, false, false);
      return true;

    case BT_CMD_TEXT:
      oled_set_text((const char*)&bt_rcv_buffer[1]);
      return true;
      
    case BT_CMD_HELP:
      myBTSerial.println(F("B M[NUM] L[01][01][01] T[text]"));
      return true;
  }

  return false;
}


int bt_parse_dec(unsigned char pos)
{
  int num = 0;

  // find the end of the number. endpos points after the end.
  unsigned char endpos = pos;
  for(; endpos<bt_rcv_buffer_cnt; ++endpos) {
    if(bt_rcv_buffer[endpos] < '0' || bt_rcv_buffer[endpos] > '9') {
      break;
    }
  }
  if(endpos==pos) {
    return -1;
  }
  
  Serial.print(F("endpos: "));
  Serial.println(endpos);

  int factor = 1;
  for(; endpos != pos; --endpos) {
    num += (bt_rcv_buffer[endpos-1] - '0') * factor;
    factor *= 10;
  }

  Serial.print(F("bt-dec-num: "));
  Serial.print(num);
  return num;
}


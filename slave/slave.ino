#include <Wire.h>

#define MY_DEVICE_ADDR (0xA0>>1)
#define LED_PIN 13


int last_cmd = 0;
bool do_blink = false;


void setup()
{
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  Wire.begin(MY_DEVICE_ADDR);
  Wire.onRequest(i2c_read_buttons);
  Wire.onReceive(i2c_action);

  Serial.println("Go");
  Serial.print("Address: 0x");
  Serial.println(MY_DEVICE_ADDR << 1, HEX);
}


/**
 * Return quickly!
 */
void i2c_read_buttons()
{
  Wire.write(last_cmd); // no button pressed
}

void i2c_action(int numBytes)
{
  if (Wire.available() > 0) {
    int c = Wire.read();
    int p = 0;
    if (Wire.available() > 0) {
      p = Wire.read();
    }
    do_command(c, p);
  }
}


void do_command(int cmd, int param)
{
  Serial.print("CMD: ");
  Serial.println(cmd);
  last_cmd = cmd;
  do_blink = true;
}


void blink()
{
  Serial.println("blink");
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}


void loop()
{
  if(do_blink) {
    blink();
    do_blink = false;
  }
}

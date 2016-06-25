#include <Wire.h>

#define MY_DEVICE_ADDR (0xA0>>1)
#define I2C_CMD_GET_BUTTON 'b' // resets press event
#define I2C_CMD_GET_ROTARY 'r'
#define I2C_CMD_GET_UP 'u'
#define I2C_CMD_GET_DOWN 'd'
#define LED_PIN 13

int i2c_reply = 0xff;
bool button_is_pressed = false;
bool button_is_up = false;
bool button_is_down = false;



const int pin_A = 12;  // pin 12
const int pin_button = 11;
const int pin_B = 10;  // pin 11


unsigned long currentTime;
unsigned long loopTime;


int brightness = 120;
int prev_brightness = brightness;
int fadeAmount = 10;
unsigned char encoder_A;
unsigned char encoder_B;
unsigned char encoder_A_prev = 0;
unsigned char encoder_button = 0;


bool do_blink = false;


void setup()
{
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  Wire.begin(MY_DEVICE_ADDR);
  Wire.onRequest(i2c_read_buttons);
  Wire.onReceive(i2c_action);

  // using internal pull-up
  pinMode(pin_A, INPUT);
  digitalWrite(pin_A, HIGH);
  pinMode(pin_B, INPUT);
  digitalWrite(pin_B, HIGH);

  pinMode(pin_button, INPUT);
  digitalWrite(pin_button, HIGH);

  Serial.println("Go");
  Serial.print("i2c address: 0x");
  Serial.println(MY_DEVICE_ADDR << 1, HEX);

  currentTime = millis();
  loopTime = currentTime;
}


/**
 * Return quickly!
 */
void i2c_read_buttons()
{
  Wire.write(i2c_reply);
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
  //do_blink = true;

  switch(cmd) {
  case I2C_CMD_GET_BUTTON:
    i2c_reply = button_is_pressed;
    button_is_pressed = false;
    break;
  case I2C_CMD_GET_ROTARY:
    i2c_reply = brightness;
    break;
  case I2C_CMD_GET_UP:
    i2c_reply = button_is_up;
    button_is_up = false;
    break;
  case I2C_CMD_GET_DOWN:
    i2c_reply = button_is_down;
    button_is_down = false;
    break;
  default:
    i2c_reply = 0xff;
    break;
  }
}


void blink()
{
  Serial.println("blink");
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
}


void loop()
{
  if(do_blink) {
    blink();
    do_blink = false;
  }

  // get the current elapsed time
  currentTime = millis();
  if(currentTime >= (loopTime + 2*5)){
    // 5ms since last check of encoder = 200Hz  
    encoder_A = digitalRead(pin_A);    // Read encoder pins
    encoder_B = digitalRead(pin_B);   
    if((!encoder_A) && (encoder_A_prev)){
      // A has gone from high to low 
      if(encoder_B) {
        // B is high so clockwise
        // increase the brightness, dont go over 255
        if(brightness + fadeAmount <= 255) brightness += fadeAmount;               
        button_is_up = true;
      }   
      else {
        // B is low so counter-clockwise      
        // decrease the brightness, dont go below 0
        if(brightness - fadeAmount >= 0) brightness -= fadeAmount;               
        button_is_down = true;
      }   

    }   
    encoder_A_prev = encoder_A;     // Store value of A for next time    
    
    // set the brightness of pin 9:
    //analogWrite(9, brightness);   
    if(prev_brightness != brightness) {
      prev_brightness = brightness;
      Serial.print("brightness: ");
      Serial.println(brightness);
    }

    // check if button pressed
    unsigned char isup = digitalRead(pin_button);
    if(!isup && encoder_button) {
      button_is_pressed = true;
      Serial.println("pressed");
    }
    encoder_button = isup;
   
    loopTime = currentTime;  // Updates loopTime
  }
}

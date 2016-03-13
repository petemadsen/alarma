#ifndef I2C_H
#define I2C_H


void i2c_scan()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknow error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan
}



int read_i2c(int addr)
{
  Wire.requestFrom(addr, 1);

  if(Wire.available())     //If the request is available
  {
      return Wire.read();       //Receive the data
      //Serial.println(x);
  } else {
    Serial.println("NONE");
  }
  return -1;
}


void send_cmd(int wnd, int cmd)
{
#if 0
  Serial.print("ACTION: to 0x");
  Serial.print(wnd << 1, HEX);
  Serial.print(" cmd ");
  Serial.println(cmd);
#endif
 
  Wire.beginTransmission(wnd);
  Wire.write(cmd);
  Wire.endTransmission();
}

#endif


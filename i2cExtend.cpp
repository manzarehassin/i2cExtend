#include "i2cExtend.h"

i2cExtend::i2cExtend(void)
{
	//constructor
}

void i2cExtend::begin(byte DeviceID)
{
  _DeviceID = DeviceID;
  Wire.begin();
}

void i2cExtend::digitalWrite(byte pin, byte value)
{
  Wire.beginTransmission(_DeviceID);
  Wire.write(IO_DIGITAL_WRITE);     //MODE
  Wire.write(pin);   //PIN#
  Wire.write(value); //Value
  Wire.endTransmission();
}

byte i2cExtend::digitalRead(byte pin)
{
  Wire.beginTransmission(_DeviceID);
  Wire.write(IO_DIGITAL_READ);     //MODE
  Wire.write(pin);   //PIN#
  Wire.endTransmission();

  Wire.requestFrom(_DeviceID, 1); //Requesting
  while (Wire.available())
  {
    return Wire.read(); //Received Data
  }
}

void i2cExtend::analogWrite(byte pin, byte value)
{
  
  Wire.beginTransmission(_DeviceID);
  Wire.write(IO_ANALOG_WRITE);     //MODE
  Wire.write(pin);   //PIN#
  Wire.write(value); //Value
  Wire.endTransmission();
}

size_t i2cExtend::analogRead(byte pin)
{
  byte H=0,L=0;
  Wire.beginTransmission(_DeviceID);
  Wire.write(IO_ANALOG_READ);     //MODE
  Wire.write(pin);   //PIN#
  Wire.endTransmission();

  Wire.requestFrom(_DeviceID, 2); //Requesting
  while (Wire.available())
  {
    H= Wire.read(); //Received Data MSB
    L= Wire.read(); //Received Data MSB
  }
  return H <<8 | L;
}

byte i2cExtend::RAMread(size_t address)
{
  byte H=address >> 8; //MSB
  byte L=address;      //LSB
  
  Wire.beginTransmission(_DeviceID);
  Wire.write(RAM_READ);       //MODE
  Wire.write(H);       //Address MSB
  Wire.write(L);       //Address LSB
  Wire.endTransmission();

  Wire.requestFrom(_DeviceID, 1); //Requesting
  while (Wire.available())
  {
    return Wire.read(); //Received Data
  }
}

void i2cExtend::RAMwrite(size_t address, byte value)
{
  byte H=address >> 8; //MSB
  byte L=address;      //LSB
  
  Wire.beginTransmission(_DeviceID);
  Wire.write(RAM_WRITE);       //MODE
  Wire.write(H);       //Address MSB
  Wire.write(L);       //Address LSB
  Wire.write(value);   //Value
  Wire.endTransmission();
}

void i2cExtend::RAMflush()
{
  Wire.beginTransmission(_DeviceID);
  Wire.write(RAM_FLUSH);       //MODE
  Wire.endTransmission();
}

byte i2cExtend::EEPROMread(size_t address)
{
  byte H=address >> 8; //MSB
  byte L=address;      //LSB
  
  Wire.beginTransmission(_DeviceID);
  Wire.write(ROM_READ);       //MODE
  Wire.write(H);       //Address MSB
  Wire.write(L);       //Address LSB
  Wire.endTransmission();

  Wire.requestFrom(_DeviceID, 1); //Requesting
  while (Wire.available())
  {
    return Wire.read(); //Received Data
  }
}

void i2cExtend::EEPROMwrite(size_t address, byte value)
{
  byte H=address >> 8; //MSB
  byte L=address;      //LSB
  
  Wire.beginTransmission(_DeviceID);
  Wire.write(ROM_WRITE);       //MODE
  Wire.write(H);       //Address MSB
  Wire.write(L);       //Address LSB
  Wire.write(value);   //Value
  Wire.endTransmission();
}

void i2cExtend::pinMode(byte pin,byte mode)
{
  Wire.beginTransmission(_DeviceID);
  Wire.write(IO_SET_CONFIG); //MODE
  Wire.write(pin);           //PIN#
  
  switch(mode)
  {
    case INPUT:  Wire.write(INPUT);  break; 
	case INPUT_PULLUP:  Wire.write(INPUT_PULLUP);  break;
    case OUTPUT: Wire.write(OUTPUT); break;
  }
  Wire.endTransmission();
}

size_t i2cExtend::getConfig()
{
  byte H=0,L=0;
  
  Wire.beginTransmission(_DeviceID);
  Wire.write(IO_GET_CONFIG);       //MODE
  Wire.endTransmission();

  Wire.requestFrom(_DeviceID, 2); //Requesting
  while (Wire.available())
  {
    H= Wire.read(); //Received Data MSB
    L= Wire.read(); //Received Data MSB
  }
  return H <<8 | L;
}

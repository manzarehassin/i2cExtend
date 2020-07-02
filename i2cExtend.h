/* ==================================================================================
 *                           I2C GPIO EXTENDER LIBRARY
 * ================================================================================== 
 *  
 *  i2cExtend Library developed by Manzar E Hassin <mnz247@hotmail.com>
 *  
 *  Version 1.0.1 
 *  Release Date: Wednesday, July 1, 2020
 *  
 *  Library available at https://github.com/kittyboy2005/i2cExtend
 *  
 */



#include <Wire.h>
#define RAM_SIZE 512
#define ROM_SIZE 512

// MODE SELECT===========================
#define IO_DIGITAL_WRITE  0
#define IO_DIGITAL_READ   1
#define IO_ANALOG_WRITE   2
#define IO_ANALOG_READ    3
#define RAM_READ          4
#define RAM_WRITE         5
#define RAM_FLUSH         6
#define ROM_READ          7
#define ROM_WRITE         8
#define IO_SET_CONFIG     9 //set pinmode
#define IO_GET_CONFIG     10
#define SET_INTERRUPT     11
#define GET_INTERRUPT     12
#define GET_INFO          13

//Interrupt pins
#define INT_0 2
#define INT_1 3

#ifndef ext
#define ext

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class i2cExtend  
{
  public:
    // Constructor 
   i2cExtend();

    // Methods
    void begin(byte DeviceID = 0x19 <<2 | 0b11 );
    
    void digitalWrite(byte pin, byte value);
    byte digitalRead(byte pin);

    void analogWrite(byte pin, byte value);
    size_t analogRead(byte pin);

    byte RAMread(size_t address);
    void RAMwrite(size_t address, byte value);
    void RAMflush();

    byte EEPROMread(size_t address);
    void EEPROMwrite(size_t address, byte value);
    
    void pinMode(byte pin,byte mode);
    size_t getConfig();
    
  private:
    byte _DeviceID;
};
#endif
/* ==================================================================================
 *  I2C GPIO EXTENDER (SLAVE)
 * ================================================================================== 
 *  -------------------------------------------------------------------
 *  i2cExtend Library developed by Manzar E Hassin <mnz247@hotmail.com>
 *  -------------------------------------------------------------------
 *  
 *  For burning bootloader use MiniCore developed by MCUdude. 
 *  MiniCore Bootloader Resource available at https://github.com/MCUdude/MiniCore
 *  
 *  Microcontroller Model: Microchip ATMEGA8A
 *  Clock rate: 8 Mhz Internal
 *  Bod: Disabled
 *  Compiler LTO: Enabled
 *  Bootloader: UART0
 *  
 *  ------------------------------------------------------------------------
 *  
 *  i2cExtend Library available at https://github.com/kittyboy2005/i2cExtend
 *  
 *  ------------------------------------------------------------------------
 */

#include <Wire.h>
#include <EEPROM.h>

#define RAM_SIZE 512
#define ROM_SIZE 512

//I2C Address Parameters
#define ADDR_PREFIX 0x19
#define ADDR_L 0
#define ADDR_H 1

/* PIN INDEX--------------------
 IO_0 2
 IO_1 3
 IO_2 4
 IO_3 5
 IO_4 6
 IO_5 7
 IO_6 8
 IO_7 9
 IO_8 10
 IO_9 11
 IO_10 12
 IO_11 13
 IO_12 A0
 IO_13 A1
 IO_14 A2
 IO_15 A3

PWM enabled pins---------------

 PWM_1 9
 PWM_2 10
 PWM_3 11

//Analog pins--------------------
ANALOG_1 A0
ANALOG_2 A1
ANALOG_3 A2
ANALOG_4 A3

//Interrupt pins------------------
INT_0 2
INT_1 3
--------------------------- */

#define SDA = A4
#define SCL = A5

// MODE SELECT===================
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

// FLAG Register ==================
struct Register_FLAGS
{
  byte MODE : 4;        //To Store Mode Status (Instruction)
  byte PIN : 4;         //Pin index storage
  byte ADDRESS_H :1;    //To store address msb (Location)
  byte ADDRESS_L;       //To store address lsb (Location)
  byte VALUE_H;         //Read/Write values (MSB)
  byte VALUE_L;         //Read/Write values (LSB)
  size_t IO_pinMode:16; //IO Pinmode status storage
  byte pinMode_Type:2;  //PinMode Type Storage
 // byte INTERRUPT_OUTPUT; //Interrupt Output Pins (Config)
 // bool INT_0_EN :1 ;     //Interrupt 0 enable (digital 2) (Config)
 // bool INT_1_EN :1;      //Interrupt 1 enable (digital 3) (Config)
 // bool INT_0_MODE :1;    //Interrupt 0 mode (digital 2) (Config)
 // bool INT_1_MODE :1;    //Interrupt 1 mode (digital 3) (Config)
 //volatile bool INT_0_STATE :1 ; //Interrupt 0 function State
 //volatile bool INT_1_STATE :1 ; //Interrupt 1 function State
};
Register_FLAGS flag;
volatile byte RAM_STORAGE[RAM_SIZE]; //S-RAM Storage Array
const static byte IO_PINS[16]={2,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3}; //IO Pin Index

void Flush_RAM() //RAM-FLUSH operation (Clear entire RAM storage)
{
  for (size_t i=0;i<RAM_SIZE;i++)
  {
    RAM_STORAGE[i]=0;
  }
}

void READ_RAM() //Reading 1 byte from RAM
{
  flag.VALUE_L= RAM_STORAGE[GET_ADDRESS()];
}

void WRITE_RAM() //Writing 1 byte to RAM
{
  RAM_STORAGE[GET_ADDRESS()] = flag.VALUE_L;
}

void READ_EEPROM() //Reading 1 byte from Internal ROM
{
  flag.VALUE_L= EEPROM.read(GET_ADDRESS());
}

void WRITE_EEPROM() //Writing 1 byte to Internal ROM
{
  EEPROM.update(GET_ADDRESS(), flag.VALUE_L);
}

void SET_IO_PINMODE()
{
  switch(flag.pinMode_Type)
  {
    case INPUT:  pinMode(IO_PINS[flag.PIN],INPUT);bitWrite(flag.IO_pinMode,flag.PIN,INPUT);break;
	  case INPUT_PULLUP:  pinMode(IO_PINS[flag.PIN],INPUT_PULLUP);bitWrite(flag.IO_pinMode,flag.PIN,INPUT);break;
    case OUTPUT: pinMode(IO_PINS[flag.PIN],OUTPUT);bitWrite(flag.IO_pinMode,flag.PIN,OUTPUT);break;
  }
}

size_t GET_ADDRESS()
{
  return flag.ADDRESS_H <<8 |(flag.ADDRESS_L);
}

void GET_IO_PINMODE()
{
  flag.VALUE_H = flag.IO_pinMode >>8; //MSB
  flag.VALUE_L = flag.IO_pinMode;     //LSB
  Wire.write(flag.VALUE_H);
  Wire.write(flag.VALUE_L);
  FLUSH_FLAG();
}

void IO_Digital_Write()
{
  switch(bitRead(flag.IO_pinMode,flag.PIN))
  {
    case OUTPUT: digitalWrite(IO_PINS[flag.PIN],flag.VALUE_L); break;
    case INPUT:  break;
	  case INPUT_PULLUP:  break;
  }
}

void IO_Digital_Read()
{
  switch(bitRead(flag.IO_pinMode,flag.PIN))
  {
    case INPUT: flag.VALUE_L = digitalRead(IO_PINS[flag.PIN]); break;
	  case INPUT_PULLUP: flag.VALUE_L = digitalRead(IO_PINS[flag.PIN]); break;
    case OUTPUT: break;
  }
}

void IO_Analog_Write()
{
  switch(bitRead(flag.IO_pinMode,flag.PIN))
  {
    case OUTPUT: analogWrite(IO_PINS[flag.PIN],flag.VALUE_L); break;
    case INPUT:  break;
	  case INPUT_PULLUP:  break;
  }
}

void IO_Analog_Read()
{
  size_t _input = 0;
  switch(bitRead(flag.IO_pinMode,flag.PIN))
  {
    case INPUT: _input = analogRead(IO_PINS[flag.PIN]); break;
	  case INPUT_PULLUP: _input = analogRead(IO_PINS[flag.PIN]); break;
    case OUTPUT: break;
  }
  flag.VALUE_H = _input >>8; //MSB
  flag.VALUE_L = _input;     //LSB
}

byte I2C_ADDRESS() //I2C address selector.
{
  pinMode(ADDR_H,INPUT_PULLUP); pinMode(ADDR_L,INPUT_PULLUP);
  return ADDR_PREFIX <<2 | digitalRead(ADDR_H) << 1 | digitalRead(ADDR_L);
}

void FLUSH_FLAG()
{
  flag.MODE = flag.PIN = flag.ADDRESS_H = flag.ADDRESS_L = flag.VALUE_H = flag.VALUE_L = flag.pinMode_Type = 0; 
}

void I2C_REQ() //I2C REQUEST HANDLER
{
  switch(flag.MODE)
    {
      case IO_DIGITAL_READ:  Wire.write(flag.VALUE_L); FLUSH_FLAG(); break;
      case IO_ANALOG_READ:   Wire.write(flag.VALUE_H); Wire.write(flag.VALUE_L); FLUSH_FLAG(); break;
      case RAM_READ:         Wire.write(flag.VALUE_L); FLUSH_FLAG(); break;
      case ROM_READ:         Wire.write(flag.VALUE_L); FLUSH_FLAG(); break;
      case IO_GET_CONFIG:    GET_IO_PINMODE(); break;
    }
}

void I2C_RX(int howMany) //I2C DATA RECEIVE HANDLER
{
  (void)howMany;  // cast unused parameter to void to avoid compiler warning
  while (Wire.available())
  {
    flag.MODE = Wire.read();
    switch(flag.MODE)
    {
      case IO_DIGITAL_WRITE: flag.PIN=Wire.read(); flag.VALUE_L=Wire.read(); IO_Digital_Write(); FLUSH_FLAG(); break;
      case IO_DIGITAL_READ:  flag.PIN=Wire.read(); IO_Digital_Read(); break;
      case IO_ANALOG_WRITE:  flag.PIN=Wire.read(); flag.VALUE_L=Wire.read(); IO_Analog_Write(); FLUSH_FLAG(); break;
      case IO_ANALOG_READ:   flag.PIN=Wire.read(); IO_Analog_Read(); break;
      case RAM_READ:         flag.ADDRESS_H=Wire.read(); flag.ADDRESS_L=Wire.read(); READ_RAM(); break;
      case RAM_WRITE:        flag.ADDRESS_H=Wire.read(); flag.ADDRESS_L=Wire.read(); flag.VALUE_L=Wire.read(); WRITE_RAM(); FLUSH_FLAG(); break;
      case RAM_FLUSH:        Flush_RAM();FLUSH_FLAG(); break;
      case ROM_READ:         flag.ADDRESS_H=Wire.read(); flag.ADDRESS_L=Wire.read(); READ_EEPROM(); break;
      case ROM_WRITE:        flag.ADDRESS_H=Wire.read(); flag.ADDRESS_L=Wire.read(); flag.VALUE_L=Wire.read(); WRITE_EEPROM(); FLUSH_FLAG(); break;
      case IO_SET_CONFIG:    flag.PIN=Wire.read(); flag.pinMode_Type=Wire.read(); SET_IO_PINMODE(); FLUSH_FLAG(); break;
      case IO_GET_CONFIG:    break;
      //case SET_INTERRUPT:    break;
      //case GET_INTERRUPT:    break;
      //case GET_INFO:         break;
    }
  }
}

void setup()
{
  Wire.begin(I2C_ADDRESS());
  Wire.onReceive(I2C_RX);
  Wire.onRequest(I2C_REQ);
}

void loop()
{
	//Nothing Here
}

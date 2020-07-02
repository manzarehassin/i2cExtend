/* ==================================================================================
 *                    I2C GPIO EXTENDER LIBRARY EXAMPLE SCRIPT
 * ================================================================================== 
 *  
 *  i2cExtend Library developed by Manzar E Hassin <mnz247@hotmail.com>
 *  
 *  Version 1.0.1 
 *  Release Date: Wednesday, July 1, 2020
 *  
 *  Library available at https://github.com/kittyboy2005/i2cExtend
 *  
 *  -------------------------------------------------------------------------------------------------
 *  I2C Extend External EEPROM Storage Access. In this script, we will show you Reading/Writing operation
 *  -------------------------------------------------------------------------------------------------
 *  
 *  =========================
 *       Jumper Settings 
 *  =========================
 *  A1 | A0 | Device ID (Hex)
 *  =========================
 *   0 | 0  |  0x64
 *  -------------------------
 *   0 | 1  |  0x65
 *  -------------------------
 *   1 | 0  |  0x66
 *  -------------------------
 *   1 | 1  |  0x67 (Default)
 *  -------------------------
 *  
 *  
 */

 
#include <i2cExtend.h>

i2cExtend i2cStorage; // Creating the object of i2cExtend library. The object name is i2cStorage.

void setup() 
{
	Serial.begin(9600);     //initializing Serial Interface with a baud rate of 9600 bps.
 
	i2cStorage.begin();           //Initializing I2C Extend Library with default device ID. 
  //i2cStorage.begin(0x64);     //It can also initialize like this, when device id is not default.

  READ(); 						  //Reading previously stored values

  Serial.println();
  Serial.println();
  delay(2000);          //Wait for 2 seconds
  
  WRITE(); 						//Writing random numbers

  Serial.println();
  Serial.println();
  delay(2000);        //Wait for 2 seconds
  
  READ(); 						//Reading again for verification

  Serial.println();
  Serial.println("Done!");
}

void WRITE() //WRITING OPERATION
{
  byte value=0;           //EEPROM read/write value storage

  Serial.println("Writing to External EEPROM...");
  Serial.println();
  Serial.println();
  Serial.println("Address \t Value");
  
  for(int i=0;i<ROM_SIZE;i++)
  {
    Serial.print(i);           //Printing Address
    Serial.print ("\t\t");     //Printing tab
    value = random(0,255);     //generating random values from 0 to 255
    Serial.println(value,HEX); //Printing the value in Hex
    //=====================================================================
    i2cStorage.EEPROMwrite(i,value); //Writing the value into ith location
	//=====================================================================
  }
}

void READ() //READING OPERATION
{
  Serial.println("Reading From External EEPROM...");
  Serial.println();
  Serial.println();
  Serial.println("Address \t Value");
  
  byte value =0;
  
  for(int i=0;i<ROM_SIZE;i++)
  {
    Serial.print(i);                 //Printing Address
    Serial.print ("\t\t");           //Printing tab
    //========================================================================
    value = i2cStorage.EEPROMread(i);//reading values from external EEPROM.
    //========================================================================
    Serial.println(value, HEX);      //Printing the value in Hex
  }
}

void loop()
{
  //Nothing Here
}

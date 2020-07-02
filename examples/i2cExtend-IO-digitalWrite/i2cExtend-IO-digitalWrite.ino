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
 *  I2C Extend GPIO Access. In this script, we will show you digitalWrite() methods. Connect a LED through a 220Ohm resistor to AtMega8 Physical Pin 19 (IO11). And connect the ground leg to ground terminal.
 *  -------------------------------------------------------------------------------------------------
 *  
 *  For pinout, Visit: https://github.com/kittyboy2005/i2cExtend/blob/master/Pinouts/i2cExtend_ATMEGA8A_Pinout_Screen.png
 *  
 *  
 * You can use a total of 4 extender at a time by changing jumper settings of the device ID address line. If shorted to ground then it represents o. Otherwise, it represents 1.
 *  =========================
 *       Jumper Settings 
 *  =========================
 *  A1 | A0 | Device ID (Hex)
 *  =========================
 *   0 | 0  |  0x64
 *  -------------------------
 *   0 } 1  |  0x65
 *  -------------------------
 *   1 } 0  |  0x66
 *  -------------------------
 *   1 } 1  |  0x67 (Default)
 *  -------------------------
 *  
 *  
 */

 
#include <i2cExtend.h>

i2cExtend GPIO; // Creating the object of i2cExtend library. The object name is GPIO.

void setup() 
{
	Serial.begin(9600);     //initializing Serial Interface with a baud rate of 9600 bps.
 
	GPIO.begin();           //Initializing I2C Extend Library with default device ID. 
  //GPIO.begin(0x64);     //It can also initialize like this, when device id is not default.
  
	GPIO.pinMode(11,OUTPUT); //We are declaring IO11 (ATMEGA8A Physical pin number 19) as Output
}

void loop()
{
  // Simple Blinking Sketch. Turn on LED for one second and then turn off for one second.
  GPIO.digitalWrite(11,HIGH);
  Serial.println("LED on");
  delay(1000);
  GPIO.digitalWrite(11,LOW);
  Serial.println("LED off");
  delay(1000);
}

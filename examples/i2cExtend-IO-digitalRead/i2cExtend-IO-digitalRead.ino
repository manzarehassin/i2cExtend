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
 *  Connect a momentary push button across to AtMega8 Physical Pin 4 (IO0) and ground terminal.
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

const byte Button = 0; //We are declaring IO0 (ATMEGA8A Physical pin number 4) as Button pin
const byte LED = 11;   //We are declaring IO11 (ATMEGA8A Physical pin number 19) as LED pin

void setup() 
{
	GPIO.begin();           //Initializing I2C Extend Library with default device ID. 
  //GPIO.begin(0x64);     //It can also initialize like this, when device id is not default.
  
	GPIO.pinMode(LED,OUTPUT);          //We are declaring IO11 (ATMEGA8A Physical pin number 19) as Output
  GPIO.pinMode(Button,INPUT_PULLUP); //We are declaring IO0 (ATMEGA8A Physical pin number 4) as Input
}

void loop()
{
  bool Result = GPIO.digitalRead(Button); //Reading the state of the button. After that store that status into Result variable.
  GPIO.digitalWrite(LED,Result);          //Writing button status into LED pin. When button is pressed, then the LED will turned off. Otherwise led remain turned on.
  delay(50);                              // A small delay
}

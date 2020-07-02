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
 *  -----------------------------------------------------------------------------------------------------------------------
    Reads an analog input on AtMega8 Physical Pin 23 (IO12), prints the result to the Serial Monitor.
    Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
    Attach the center pin of a potentiometer to AtMega8 Physical Pin 23 (IO12), and the outside pins to +5V and ground.
 *  -----------------------------------------------------------------------------------------------------------------------
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

i2cExtend GPIO; // Creating the object of i2cExtend library. The object name is GPIO.

const byte Pot = 12; //We are declaring IO12 as Pot pin

void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
	GPIO.begin();           //Initializing I2C Extend Library with default device ID. 
  //GPIO.begin(0x64);     //It can also initialize like this, when device id is not default.
  
  GPIO.pinMode(Pot,INPUT); //We are declaring IO12 as Input
}

void loop()
{
  int SensorValue = GPIO.analogRead(Pot); //Reading the state of the button. After that store that status into SensorValue variable.
  // print out the value you read:
  Serial.println(SensorValue);
  delay(1);        // delay in between reads for stability
}

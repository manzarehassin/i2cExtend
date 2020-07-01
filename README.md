# i2cExtend
I2C protocol based I/O Pin extender, external RAM, EEPROM access library for Arduino environment.

* 16 external IO pins available (as input and output)
* 4 Analog Read/ Write Pins. 10 Bits ADC.
* 3 PWM capable pins
* 512 bytes External Static Ram storage access
* 512 bytes External EEPROM storage access
* 2 Interrupt Access (Coming soon)

**_Use ATMEGA8A microcontroller as GPIO extender (I2C Slave)._** 

_Still in Beta version. Full version is coming soon._

# _Static RAM Storage Access_

## Reading: 
### RAMread(Address)
**Address:** Target address location. _Valid address location: 0-511_.

**Returns** 1 byte of data.




## Writing: 
### RAMwrite(Address,Value)

**Address:** Target address location. _Valid address location: 0-511_.

**Value:** 1 byte of data which will be written into RAM storage.

**Returns** nothing.




## Erase RAM Storage: 
### RAMflush()

**Returns** nothing.



# _EEPROM Storage Access_

## Reading: 
### EEPROMread(Address)
**Address:** Target address location. _Valid address location: 0-511_.

**Returns** 1 byte of data.




## Writing: 
### EEPROMwrite(Address,Value)

**Address:** Target address location. _Valid address location: 0-511_.

**Value:** 1 byte of data which will be written into RAM storage.

**Returns** nothing.



# _Extended IO Access_

It provides total 16 IO pins. All of those can be acts as digital pins. Additionally, 4 pins are capable of **analogRead()** function. As a result, it can read analog values from those pins. 3 pins are PWM capable. So, you can perform traditional **analogWrite()** operation.

## Set Pin Modes:

### pinMode(Pin, Mode)

**Pin** : Target pin to set the mode

**Mode**: Valid Pin modes are **INPUT** (for normal input), **OUTPUT** (for output), **INPUT_PULLUP** (for input as pullup)

**Returns** nothing.



## Get Pin Modes Configuration:

### getConfig()

**Returns** 16 bits Integer. Where **0** represents input and **1** represents output





## Digital Write:

### digitalWrite(Pin, Value)

**Pin** : Target pin for writing operation

**Value**: Value which will be written to target pin. Valid values are **HIGH** or **LOW**

**Returns** nothing.


## Digital Read:

### digitalRead(Pin)

**Pin** : Target pin for reading operation

**Returns** one bit of data.





## Analog Write:

### analogWrite(Pin, Value)

**Pin** : Target pin for writing operation

**Value**: Value which will be written to target pin. Valid values are 0-255.

**Returns** nothing.





## Analog Read:

### analogRead(Pin)

**Pin** : Target pin for reading operation

**Returns** 10 bits of integer data (similar to unsigned int).

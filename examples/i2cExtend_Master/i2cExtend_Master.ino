#include <i2cExtend.h>

i2cExtend e;

void setup() 
{
	Serial.begin(9600);
	e.begin();
	e.pinMode(11,OUTPUT);
	
	//RAM Write access
	Serial.println("Storing data to external ram...");
	for(int i=0;i<RAM_SIZE;i++)
	{
		
		e.RAMwrite(i,random(0,255));
	}
	
	Serial.println("Reading data from external ram...");
	//RAM READ access
	for(int i=0;i<RAM_SIZE;i++)
	{
		Serial.print(i);
		Serial.print("\t");
		Serial.println(e.RAMread(i));
	}
	
}

void loop()
{	//Accessing IO Pins
	e.digitalWrite(11,HIGH);
	delay(100);
	e.digitalWrite(11,LOW);
	delay(100);
}


/*
 Name:		GreenHouse.ino
 Created:	5/1/2018 9:03:26 PM
 Author:	Allyn
*/

// the setup function runs once when you press reset or power the board
#include <OneWire.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
enum CMDS
{
	reset = 0,
	setUp,
	getTemp,
	getHumidity,
	setAlarm,
	setValve,
	setAir,
	getSoil,
	setSoil,
	findOnewire,
	findI2c
};
enum COMPLETION 
{
	failer,
	succes
};
//change pin
void setup()
{
	byte humidity;// stores the indoor humidity
	byte addresses[5];//stores addresses for the one-wire devices
	byte soilWaterLevel[5];
	byte tempurature[5];
	//bellow is used for one wire devces
	OneWire wire = OneWire(8);
	Main();
	//wire.search(address);
}

// the loop function runs over and over again until power down or reset

void Main()
{
	Serial.begin(9600);
	while (true)
	{
		if (Serial.available())
		{
			byte cmd = Serial.read();
			switch (cmd)
			{
			case reset:
				Reset();
				break;
			case getTemp:
				GetTemp();
				break;
			case getHumidity:
				GetHumidity();
				break;
			case setAlarm:
				SetAlarm();
				break;
			case setValve:
				SetValve();
				break;
			case setAir:
				SetAir();
				break;
			case getSoil:
				GetSoil();
				break;
			case setSoil:
				SetSoil();
				break;
			default:
				Serial.write(failer);
				break;
			}
		}
		Update();
		Display();
	}
}

void Display()
{

}
void Update(byte addresses[],int addressesLength,byte tempurature[],OneWire wire)// check all sensors and set controls
{
	// have all devices convert first
	wire.skip();
	wire.write(0x44,1);
	
	for (int addressesIndex  = 0; addressesIndex < addressesLength; addressesIndex++)//check one wire
	{
		const uint8_t select = addresses[addressesIndex];
		wire.select(select);
	}

}
void Reset() //?
{

}
void GetTemp()//get tempurature of green house and outdoors
{

}
void GetHumidity()//get the humidity of the green house
{

}
void SetAlarm()//set alarms if tempurature is outside of certin bounds
{

}
void SetValve()//set water valves
{

}
void SetValve(byte addr)//set water valves
{

}
void SetAir()//controls temp by controlling stepper on air valve
{

}
void GetSoil()//get soil moistuer level
{

}
byte GetSoil(byte addr)//get soil moistuer level
{

}
void SetSoil()//set soil moisture level
{

}
void SetSoil(byte addr)//set soil moisture level SET while at optimal levels
{

}




/*
 Name:		GreenHouse.ino
 Created:	5/1/2018 9:03:26 PM
 Author:	Allyn
*/

// the setup function runs once when you press reset or power the board
#include <Wire.h>
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
struct Zone
{
	byte currentMoistureLevel;
	byte setMoistureLevel;
	byte valveStatus;
	byte moistureSensorAdress;
	byte valveAdress;
	int_fast8_t valveOverRide;
};
void setup()
{


	//bellow is used for one wire devces

	Main();
	//wire.search(address);
}
// the loop function runs over and over again until power down or reset

void Main()
{
	TwoWire i2c;
	i2c.begin();
	OneWire wire = OneWire(8);
	Zone Zones[10];
	byte displayStat = 0;
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



void Display(byte state, Zone zones[], byte zonesLength, byte address)
{
	//switch for buttons
	//
	//
	state = state >= zonesLength ? 0 : state;
	byte letter = state + 0x41;
	// write to i2c device


}
void Update(Zone Zones[], uint8_t zoneLength, OneWire wire, TwoWire twoWire)// check all sensors and set controls
{

	for (int zone = 0; zone < zoneLength; ++zone)
	{
		//get moisture level from multichannel analog to i2c converter
		//Zones[zone].currentMoistureLevel = twoWire.requestFrom()
		Zones[zone].valveStatus = Zones[zone].setMoistureLevel <= Zones[zone].currentMoistureLevel ? 0 : 255;
	}

}
void Reset() //?
{

}
byte GetTemp(byte addr, OneWire wire)//get tempurature of green house and outdoors
{
	wire.select(addr);
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




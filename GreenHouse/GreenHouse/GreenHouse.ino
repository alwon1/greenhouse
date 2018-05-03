/*
 Name:		GreenHouse.ino
 Created:	5/1/2018 9:03:26 PM
 Author:	Allyn
*/

// the setup function runs once when you press reset or power the board
#include <TimeLib.h>
#include <Time.h>
#include <Wire.h>
#include <OneWire.h>
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
	byte i2cAdress;//use same analog to i2c for both moisture and flowrate
	byte moistureSensorRegistar;
	byte flowMeterRegistar;
	byte valveAdress;
	int_fast8_t valveOverRide;
	byte waterFlowRate;//current water flow rate
	unsigned long waterUsage;//reset when checked
	//unsigned long lastUpdate; //stores the time of the last update
};
void setup()
{

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
		// add timer
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
	//TODO turn off moisture sensors power when not in use
	for (int zone = 0; zone < zoneLength; ++zone)
	{
		twoWire.beginTransmission(Zones[zone].i2cAdress);
		twoWire.write(Zones[zone].moistureSensorRegistar);
		twoWire.write(Zones[zone].flowMeterRegistar);
		twoWire.endTransmission();
		Zones[zone].currentMoistureLevel = twoWire.read();
		Zones[zone].waterFlowRate = twoWire.read();
		//Zones[zone].lastUpdate = millis();
		Zones[zone].valveStatus = Zones[zone].setMoistureLevel <= Zones[zone].currentMoistureLevel ? 0 : 255;
		Zones[zone].valveStatus = Zones[zone].valveOverRide == 0 ? Zones[zone].valveStatus : Zones[zone].valveOverRide;
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
void SetValve(Zone zone,byte value)//set water valves
{
	zone.valveOverRide = value;
}
void SetValve(byte addr)//set water valves
{

}
void SetAir()//controls temp by controlling stepper on air valve
{

}
void GetSoil(Zone zones[],byte zonesLength)//get soil moistuer level
{

	for (uint8_t zone = 0; zone < zonesLength; ++zone) 
	{

	}
}
byte GetSoil(Zone zone)//get soil moistuer level
{
	return zone.currentMoistureLevel;
}
void SetSoil(Zone zone)//set soil moisture level
{
	zone.setMoistureLevel = zone.currentMoistureLevel;
}
void SetSoil(byte addr)//set soil moisture level SET while at optimal levels
{

}




#include "VehicleFactory.h"

VehicleFactory::VehicleFactory(void)
{
}


VehicleFactory::~VehicleFactory(void)
{
}

Vehicle * VehicleFactory::createVehicle(std::string vehicleType)
{
	if (vehicleType == "Car")
	{
		return new Car();
	}
	else if (vehicleType == "Bus")
	{
		return new Bus();
	}
	else if (vehicleType == "Truck")
	{
		return new Truck();
	}
	else if (vehicleType == "Log")
	{
		return new Log();
	}
	else if (vehicleType == "DisappearingLog")
	{
		return new DisappearingLog();
	}
	else
	{
		return NULL; //this is an error, should throw an exception
	}
}

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
		return Car::create();
	}
	else if (vehicleType == "Bus")
	{
		return Bus::create();
	}
	else if (vehicleType == "Truck")
	{
		return Truck::create();
	}
	else if (vehicleType == "Log")
	{
		return Log::create();
	}
	else if (vehicleType == "DisappearingLog")
	{
		return DisappearingLog::create();
	}
	else
	{
		return NULL; //this is an error, should throw an exception
	}
}

#ifndef VEHICLE_FACTORY_H
#define VEHICLE_FACTORY_H

#include "Vehicle.h"
#include "Car.h"
#include "Bus.h"
#include "Truck.h"
#include "Log.h"
#include "DisappearingLog.h"

class VehicleFactory
{
public:
	VehicleFactory(void);
	~VehicleFactory(void);
	Vehicle * createVehicle(std::string vehicleType);
};

#endif


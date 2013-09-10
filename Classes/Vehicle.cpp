#include "Vehicle.h"

using namespace cocos2d;

Vehicle::Vehicle(void)
{
}

int Vehicle::getSpeed()
{
	return _speed;
}

CCPoint Vehicle::getOrigin()
{
	return _origin;
}

CCPoint Vehicle::getDestination()
{
	return _destination;
}

Vehicle::~Vehicle(void)
{
}
#include "Vehicle.h"

using namespace cocos2d;

Vehicle::Vehicle(void)
{
}

int Vehicle::getSpeed()
{
	return _speed;
}

void Vehicle::setSpeed(int speed)
{
	_speed = speed;
}

CCPoint Vehicle::getOrigin()
{
	return _origin;
}

CCPoint Vehicle::getDestination()
{
	return _destination;
}

void Vehicle::setDestination(cocos2d::CCPoint destination)
{
	_destination = destination;
}

Vehicle::~Vehicle(void)
{
}

void Vehicle::setMovementAction(CCFiniteTimeAction * action)
{
	_movementAction = action;
}

CCFiniteTimeAction * Vehicle::getMovementAction()
{
	return _movementAction;
}
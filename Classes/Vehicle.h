#ifndef VEHICLE_H
#define VEHICLE_H

#include "SpriteContainer.h"

class Vehicle : public SpriteContainer
{
protected:
	int _speed;
public:
	Vehicle(void);
	~Vehicle(void);
	int getSpeed();
};

#endif
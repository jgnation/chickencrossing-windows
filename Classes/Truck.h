#ifndef TRUCK_H
#define TRUCK_H

#include "cocos2d.h"
#include "Vehicle.h"

class Truck : public Vehicle
{
public:
	Truck(void);
	~Truck(void);
	CREATE_FUNC(Truck);
	virtual bool init();
};

#endif


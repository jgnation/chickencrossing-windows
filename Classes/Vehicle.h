#ifndef VEHICLE_H
#define VEHICLE_H

#include "SpriteContainer.h"

class Vehicle : public SpriteContainer
{
protected:
	int _speed;
	cocos2d::CCPoint _origin;
	cocos2d::CCPoint _destination;
public:
	Vehicle(void);
	~Vehicle(void);
	int getSpeed();
	cocos2d::CCPoint getOrigin();
	cocos2d::CCPoint getDestination();
};

#endif
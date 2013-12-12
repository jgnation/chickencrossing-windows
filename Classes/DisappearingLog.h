#ifndef DISAPPEARING_LOG_H
#define DISAPPEARING_LOG_H

#include "cocos2d.h"
#include "Vehicle.h"

class DisappearingLog :	public Vehicle
{
public:
	DisappearingLog(void);
	~DisappearingLog(void);

	float getTimeTick();

	void move();
};

#endif


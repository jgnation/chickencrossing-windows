#ifndef DISAPPEARING_LOG_H
#define DISAPPEARING_LOG_H

#include "cocos2d.h"
#include "Vehicle.h"
#include "Log.h"

class DisappearingLog :	public Log
{
public:
	DisappearingLog(void);
	~DisappearingLog(void);

	float getTimeTick();

	void move();
};

#endif


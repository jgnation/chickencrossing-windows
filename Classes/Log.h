#ifndef LOG_H
#define LOG_H

#include "cocos2d.h"
#include "Vehicle.h"

class Log : public Vehicle
{
public:
	Log(void);
	~Log(void);
	virtual bool init();
	CREATE_FUNC(Log);
};

#endif


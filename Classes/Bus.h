#ifndef BUS_H
#define BUS_H

#include "cocos2d.h"
#include "Vehicle.h"

class Bus : public Vehicle
{
public:
	Bus(void);
	~Bus(void);
	CREATE_FUNC(Bus);
	virtual bool init();
};

#endif
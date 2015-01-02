#ifndef CAR_H
#define CAR_H

#include "cocos2d.h"
#include "Vehicle.h"

class Car : public Vehicle
{
public:
	Car(void);
	~Car(void);
	CREATE_FUNC(Car);
	virtual bool init();
};

#endif
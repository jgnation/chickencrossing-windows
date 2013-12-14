#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "cocos2d.h"

class Dimensions
{
private:
	float _laneWidth;
public:
	Dimensions(void);
	~Dimensions(void);

	static float getLaneWidth();
	static bool moveIsValid();
};

#endif


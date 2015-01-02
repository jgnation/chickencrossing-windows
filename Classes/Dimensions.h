#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "cocos2d.h"

class Chicken; //foward declaration
class Dimensions
{
private:
	Dimensions(void);
	~Dimensions(void);

	static const int NUM_OF_LANES = 16;
public:
	//Dimensions(void);
	//~Dimensions(void);

	static float getLaneWidth();
	static bool moveIsInPlayableArea(cocos2d::CCPoint, Chicken * chicken);
	static float getLanePixelValue(int laneNumber);
	static int getLaneNumber(float pixelPosition);
};

#endif


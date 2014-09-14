#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "cocos2d.h"

class Chicken; //foward declaration
class Dimensions
{
private:
	static const int NUM_OF_LANES = 16;
	cocos2d::CCSize _windowSize;

	float _laneWidth;
public:
	Dimensions(void);
	~Dimensions(void);

	float getLaneWidth();
	bool moveIsInPlayableArea(cocos2d::CCPoint, Chicken * chicken);
	float getLanePixelValue(int laneNumber);
	float getCenterOfLanePixelValue(int laneNumber);
	int getLaneNumber(float pixelPosition);
};

#endif


#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "cocos2d.h"

class Dimensions
{
private:
	static const int NUM_OF_LANES = 16;
	cocos2d::CCSize _windowSize;
	cocos2d::CCRect * _playableArea;
	float _laneWidth;
public:
	Dimensions(void);
	~Dimensions(void);

	float getLaneWidth();
	bool moveIsValid(cocos2d::CCPoint);
	float getCenterOfLanePixelValue(int laneNumber);
	int getLaneNumber(float pixelPosition);
};

#endif


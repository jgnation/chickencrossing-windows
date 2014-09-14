#include "Dimensions.h"
#include "Chicken.h"
#include <cmath>

using namespace cocos2d;

//these should probably be in a namespace, not a class
//or as a static singleton object like CCdirector
Dimensions::Dimensions(void)
{
	_windowSize = CCDirector::sharedDirector()->getWinSize();
	_laneWidth = _windowSize.height / NUM_OF_LANES;
}

Dimensions::~Dimensions(void)
{
}

float Dimensions::getLaneWidth()
{
	return _laneWidth;
}

bool Dimensions::moveIsInPlayableArea(CCPoint point, Chicken * chicken)
{
	//TODO: this method may belong in Chicken, not in Dimensions.
	//initialize this only once
	static CCRect * _playableArea = new CCRect(0, _laneWidth, (_windowSize.width - chicken->getSprite()->getContentSize().width), _windowSize.height - (_laneWidth * 4));
	if (_playableArea->containsPoint(point))
	{
		return true;
	}
	return false;
}

float Dimensions::getCenterOfLanePixelValue(int laneNumber)
{
	//I no longer have to use this method after setting the vehicle sprite's anchor points to (0,0)
	float lanePosition = (_laneWidth) * laneNumber;
	return lanePosition - (_laneWidth / 2); //return the center of the lane
}

float Dimensions::getLanePixelValue(int laneNumber)
{
	float lanePosition = (_laneWidth) * laneNumber;
	return lanePosition - (_laneWidth); //return the center of the lane
}

int Dimensions::getLaneNumber(float pixelPosition)
{
	float lane = pixelPosition / _laneWidth; //this will return the lane in indexes from 0
	lane++; //add 1 to get the lane in natural index (from 1)
	int laneNumber = static_cast <int> (std::floor(lane)); //is this fragile?
	return laneNumber;
}

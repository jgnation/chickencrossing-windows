#include "Dimensions.h"
#include <cmath>

using namespace cocos2d;

//these should probably be in a namespace, not a class
//or as a static singleton object like CCdirector
Dimensions::Dimensions(void)
{
	_windowSize = CCDirector::sharedDirector()->getWinSize();
	_laneWidth = _windowSize.height / NUM_OF_LANES;

	_playableArea = new CCRect(0, _laneWidth, _windowSize.width, _windowSize.height - (_laneWidth * 3));
}

Dimensions::~Dimensions(void)
{
}

float Dimensions::getLaneWidth()
{
	return _laneWidth;
}

bool Dimensions::moveIsInPlayableArea(CCPoint point)
{
	if (_playableArea->containsPoint(point))
	{
		return true;
	}
	return false;
}

float Dimensions::getCenterOfLanePixelValue(int laneNumber)
{
	float lanePosition = (_laneWidth) * laneNumber;
	return lanePosition - (_laneWidth / 2); //return the center of the lane
}

int Dimensions::getLaneNumber(float pixelPosition)
{
	float lane = pixelPosition / _laneWidth; //this will return the lane in indexes from 0
	lane++; //add 1 to get the lane in natural index (from 1)
	int laneNumber = static_cast <int> (std::floor(lane)); //is this fragile?
	return laneNumber;
}

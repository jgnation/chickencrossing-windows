#include "Dimensions.h"
#include "Chicken.h"
#include <cmath>

using namespace cocos2d;

//these should probably be in a namespace, not a class
//or as a static singleton object like CCdirector
Dimensions::Dimensions(void)
{
}

Dimensions::~Dimensions(void)
{
}

float Dimensions::getLaneWidth()
{
	Size windowSize = CCDirector::sharedDirector()->getWinSize();
	return windowSize.height / NUM_OF_LANES;;
}

bool Dimensions::moveIsInPlayableArea(CCPoint point, Chicken * chicken)
{
	Size windowSize = CCDirector::sharedDirector()->getWinSize();
	float chickenWidth = chicken->getSprite()->getBoundingBox().size.width;
	float laneWidth = Dimensions::getLaneWidth();
	static Rect playableArea(0, laneWidth, (windowSize.width - chickenWidth), windowSize.height - (laneWidth * 4));
	if (playableArea.containsPoint(point))
	{
		return true;
	}
	return false;
}

float Dimensions::getLanePixelValue(int laneNumber)
{
	float laneWidth = Dimensions::getLaneWidth();
	float lanePosition = (laneWidth) * laneNumber;
	return lanePosition - (laneWidth); //return the center of the lane
}

int Dimensions::getLaneNumber(float pixelPosition)
{
	float laneWidth = Dimensions::getLaneWidth();
	float lane = pixelPosition / laneWidth; //this will return the lane in indexes from 0
	lane++; //add 1 to get the lane in natural index (from 1)
	int laneNumber = static_cast <int> (std::floor(lane)); //is this fragile?
	return laneNumber;
}

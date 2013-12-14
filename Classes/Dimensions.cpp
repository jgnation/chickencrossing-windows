#include "Dimensions.h"

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
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	return windowSize.height / 16;
}

bool Dimensions::moveIsValid()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float laneWidth = Dimensions::getLaneWidth();
	return true;
}

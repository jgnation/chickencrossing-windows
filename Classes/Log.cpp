#include "Log.h"
#include "GameLayer.h"

using namespace cocos2d;

Log::Log(void)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_origin = ccp(windowSize.width, 40);
	_destination = ccp(0, 40);
	_sprite = CCSprite::create("log_small.png", CCRectMake(0, 0, 300, 93));
	_sprite->retain();
	_sprite->setPosition(ccp(windowSize.width, 40));
	_speed = 3;
}

Log::~Log(void)
{
	_sprite->release();
}

#include "Truck.h"
#include "GameLayer.h"

using namespace cocos2d;

Truck::Truck(void)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_origin = ccp(windowSize.width, 40);
	_destination = ccp(0, 40);
	_sprite = CCSprite::create("white_truck.png", CCRectMake(0, 0, 80, 30));
	_sprite->retain();
	_sprite->setPosition(ccp(windowSize.width, 40));
	_speed = 50;
}

Truck::~Truck(void)
{
	_sprite->release();
}

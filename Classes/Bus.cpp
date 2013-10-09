#include "Bus.h"
#include "GameLayer.h"

using namespace cocos2d;

Bus::Bus(void)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_origin = ccp(windowSize.width, 40);
	_destination = ccp(0, 40);
	_sprite = CCSprite::create("bus.png", CCRectMake(0, 0, 115, 35));
	_sprite->retain();
	_sprite->setPosition(ccp(windowSize.width, 40));
	_speed = 150;
}

Bus::~Bus(void)
{
	_sprite->release();
}

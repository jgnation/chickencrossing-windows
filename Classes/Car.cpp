#include "Car.h"
#include "GameLayer.h"

using namespace cocos2d;

Car::Car(void)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_origin = ccp(windowSize.width, 40);
	_destination = ccp(0, 40);
	_sprite = CCSprite::create("red_car.png", CCRectMake(0, 0, 82, 25));
	_sprite->retain();
	_sprite->setPosition(ccp(windowSize.width, 40));
	_speed = 50;
}

Car::~Car(void)
{
	_sprite->release();
}

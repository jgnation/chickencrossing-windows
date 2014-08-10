#include "Car.h"
#include "GameLayer.h"

using namespace cocos2d;

Car::Car(void) 
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_origin = ccp(windowSize.width, 40);
	_destination = ccp(0, 40);

	float originalWidth = 82;
	float originalHeight = 25;
	_sprite = CCSprite::create("red_car.png", CCRectMake(0, 0, originalWidth, originalHeight));

	_sprite->setAnchorPoint(ccp(0,0));

	//see the chicken class for explanation
	float scaleRatio = (windowSize.height / 30) / _sprite->getContentSize().height;
	_sprite->setScale(scaleRatio);

	//see the chicken class for explanation
	float scaledWidth = originalWidth * scaleRatio;
	float scaledHeight = originalHeight * scaleRatio;
	_sprite->setContentSize(CCSize(scaledWidth, scaledHeight));

	_sprite->retain();
	_speed = 100;
}

Car::~Car(void)
{
	_sprite->release();
}

#include "Truck.h"
#include "GameLayer.h"

using namespace cocos2d;

Truck::Truck(void)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_origin = ccp(windowSize.width, 40);
	_destination = ccp(0, 40);

	//float originalWidth = 80;
	//float originalHeight = 30;
	//_sprite = CCSprite::create("white_truck.png", CCRectMake(0, 0, originalWidth, originalHeight));

	float originalWidth = 300;
	float originalHeight = 114;
	_sprite = CCSprite::create("beetle_small.png", CCRectMake(0, 0, originalWidth, originalHeight));

	_sprite->setAnchorPoint(ccp(0,0));

	//see the chicken class for explanation
	float scaleRatioY = (windowSize.height / 30) / _sprite->getContentSize().height;
	_sprite->setScaleY(scaleRatioY);
	float scaleRatioX = (windowSize.width / 10) / _sprite->getContentSize().width;
	_sprite->setScaleX(scaleRatioX);

	//see the chicken class for explanation
	float scaledWidth = originalWidth * scaleRatioX;
	float scaledHeight = originalHeight * scaleRatioY;
	_sprite->setContentSize(CCSize(scaledWidth, scaledHeight));

	_sprite->retain();
	_speed = 100;
}

Truck::~Truck(void)
{
	_sprite->release();
}

#include "Log.h"
#include "GameLayer.h"

using namespace cocos2d;

Log::Log(void)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_origin = ccp(windowSize.width, 40);
	_destination = ccp(0, 40);

	float originalWidth = 300;
	float originalHeight = 93;
	_sprite = CCSprite::create("log_small.png", CCRectMake(0, 0, originalWidth, originalHeight));

	_sprite->setAnchorPoint(ccp(0,0));

	//see the chicken class for explanation
	float scaleRatio = (windowSize.height / 20) / _sprite->getContentSize().height;
	_sprite->setScale(scaleRatio);

	//see the chicken class for explanation
	float scaledWidth = originalWidth * scaleRatio;
	float scaledHeight = originalHeight * scaleRatio;
	_sprite->setContentSize(CCSize(scaledWidth, scaledHeight));

	_sprite->retain();
	_speed = 100;
}

Log::~Log(void)
{
	_sprite->release();
}

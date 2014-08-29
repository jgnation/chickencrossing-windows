#include "DisappearingLog.h"
#include "GameLayer.h"

using namespace cocos2d;

DisappearingLog::DisappearingLog(void)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_origin = ccp(windowSize.width, 40);
	_destination = ccp(0, 40);

	float originalWidth = 300;
	float originalHeight = 93;
	_sprite = CCSprite::create("log_small.png", CCRectMake(0, 0, originalWidth, originalHeight));

	_sprite->setAnchorPoint(ccp(0,0));

	//see the chicken class for explanation
	float scaleRatioY = (windowSize.height / 20) / _sprite->getContentSize().height;
	_sprite->setScaleY(scaleRatioY);
	float scaleRatioX = (windowSize.width / 4) / _sprite->getContentSize().width;
	_sprite->setScaleX(scaleRatioX);

	//see the chicken class for explanation
	float scaledWidth = originalWidth * scaleRatioX;
	float scaledHeight = originalHeight * scaleRatioY;
	_sprite->setContentSize(CCSize(scaledWidth, scaledHeight));

	_sprite->retain();
	_speed = 100;
}

DisappearingLog::~DisappearingLog(void)
{
	_sprite->release();
}

float DisappearingLog::getTimeTick() 
{
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (float) millisecs;
}

void DisappearingLog::move()
{
	Vehicle::move();

	//TODO should these times be dependent on the _duration of the log?
	CCFadeTo* fadeOut = CCFadeTo::create(0.5, 0);
	CCFadeTo* stayHidden = CCFadeTo::create(0.25, 0);
	CCFadeTo* fadeIn = CCFadeTo::create(0.5, 255);
	CCFadeTo* stayExposed = CCFadeTo::create(1.5, 255);
	CCArray * arrayOfAction = CCArray::create();
	arrayOfAction->addObject(fadeOut);
	arrayOfAction->addObject(stayHidden);
	arrayOfAction->addObject(fadeIn);
	arrayOfAction->addObject(stayExposed);
	CCSequence* pulseSequence = CCSequence::create(arrayOfAction);
	CCRepeatForever* repeat = CCRepeatForever::create(pulseSequence);
	this->getSprite()->runAction(repeat);
}

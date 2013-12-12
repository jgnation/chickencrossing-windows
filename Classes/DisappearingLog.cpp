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

	//see the chicken class for explanation
	float scaleRatio = (windowSize.height / 20) / _sprite->getContentSize().height;
	_sprite->setScale(scaleRatio);

	//see the chicken class for explanation
	float scaledWidth = originalWidth * scaleRatio;
	float scaledHeight = originalHeight * scaleRatio;
	_sprite->setContentSize(CCSize(scaledWidth, scaledHeight));

	_sprite->retain();
	_sprite->setPosition(ccp(windowSize.width, 40));
	//_speed = 150;
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

	CCFadeTo* fadeOut = CCFadeTo::create(0.5, 0);
	CCFadeTo* stayHidden = CCFadeTo::create(1.0, 0);
	CCFadeTo* fadeIn = CCFadeTo::create(0.5, 255);
	CCFadeTo* stayExposed = CCFadeTo::create(3, 255);
	CCArray * arrayOfAction = CCArray::create();
	arrayOfAction->addObject(fadeOut);
	arrayOfAction->addObject(stayHidden);
	arrayOfAction->addObject(fadeIn);
	arrayOfAction->addObject(stayExposed);
	CCSequence* pulseSequence = CCSequence::create(arrayOfAction);
	CCRepeatForever* repeat = CCRepeatForever::create(pulseSequence);
	this->getSprite()->runAction(repeat);
}

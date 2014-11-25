#include "DisappearingLog.h"
#include "GameLayer.h"

using namespace cocos2d;

DisappearingLog::DisappearingLog(void)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_origin = ccp(windowSize.width, 40);
	_destination = ccp(0, 40);

	//float originalWidth = 300;
	//float originalHeight = 93;
	//_sprite = CCSprite::create("log_small.png", CCRectMake(0, 0, originalWidth, originalHeight));

	float originalWidth = 300;
	float originalHeight = 103;
	_sprite = CCSprite::create("plank_small.png", CCRectMake(0, 0, originalWidth, originalHeight));

	_sprite->setAnchorPoint(ccp(0,0));

	//see the chicken class for explanation
	float scaleRatioY = (windowSize.height / 20) / _sprite->getContentSize().height;
	_sprite->setScaleY(scaleRatioY);
	float scaleRatioX = (windowSize.width / 4) / _sprite->getContentSize().width;
	_sprite->setScaleX(scaleRatioX);

	//see the chicken class for explanation
	float scaledWidth = originalWidth * scaleRatioX;
	float scaledHeight = originalHeight * scaleRatioY;
	//_sprite->setContentSize(CCSize(scaledWidth, scaledHeight));

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

	//these values may need to be tinkered with
	//they may need to be configurable, and maybe different from egg scramble mode and main mode
	float fadeDuration = _duration / 17.0;
	float hideDuration = _duration / 10.0;
	float showDuration = _duration / 4.0;

	CCFadeTo* fadeOut = CCFadeTo::create(fadeDuration, 0);
	CCFadeTo* stayHidden = CCFadeTo::create(hideDuration, 0);
	CCFadeTo* fadeIn = CCFadeTo::create(fadeDuration, 255);
	CCFadeTo* stayExposed = CCFadeTo::create(showDuration, 255);
	Vector<FiniteTimeAction *> allActions;
	allActions.pushBack(fadeOut);
	allActions.pushBack(stayHidden);
	allActions.pushBack(fadeIn);
	allActions.pushBack(stayExposed);
	CCSequence* pulseSequence = CCSequence::create(allActions);
	CCRepeatForever* repeat = CCRepeatForever::create(pulseSequence);
	this->getSprite()->runAction(repeat);
}

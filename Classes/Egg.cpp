#include "Egg.h"

using namespace cocos2d;

Egg::Egg() 
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	float originalWidth = 50;
	float originalHeight = 68;
	_sprite = CCSprite::create("brown_egg.png", CCRectMake(0, 0, originalWidth, originalHeight));

	_sprite->setAnchorPoint(ccp(0,0));

	float scaleRatioY = (windowSize.height / 20) / _sprite->getContentSize().height; //20 because I want the image to be quite a bit smaller than the lane.
	//_sprite->setScaleY(scaleRatioY);
	_sprite->setScale(scaleRatioY);

	//float scaleRatioX = (windowSize.width / 15) / _sprite->getContentSize().width;
	//_sprite->setScaleX(scaleRatioX);

	//float scaledWidth = originalWidth * scaleRatioX;
	float scaledWidth = originalWidth * scaleRatioY;
	float scaledHeight = originalHeight * scaleRatioY;
	//_sprite->setContentSize(CCSize(scaledWidth, scaledHeight));
}

void Egg::setPosition(float x, float y)
{
	_currentPosition.x = x;
	_currentPosition.y = y;
	_sprite->setPosition(ccp(_currentPosition.x, _currentPosition.y));
}

Egg::~Egg(void) { }
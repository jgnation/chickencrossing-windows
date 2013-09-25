#include "Egg.h"

using namespace cocos2d;

Egg::Egg(float x, float y) 
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	float originalWidth = 50;
	float originalHeight = 68;
	_sprite = CCSprite::create("brown_egg.png", CCRectMake(0, 0, originalWidth, originalHeight));

	float scaleRatio = (windowSize.height / 20) / _sprite->getContentSize().height; //20 because I want the image to be quite a bit smaller than the lane.
	_sprite->setScale(scaleRatio);

	float scaledWidth = originalWidth * scaleRatio;
	float scaledHeight = originalHeight * scaleRatio;
	_sprite->setContentSize(CCSize(scaledWidth, scaledHeight));

	_currentPosition.x = x;
	_currentPosition.y = y;
	_sprite->setPosition(ccp(_currentPosition.x, _currentPosition.y));

}

void Egg::setPosition(float x, float y)
{
	_currentPosition.x = x;
	_currentPosition.y = y;
	_sprite->setPosition(ccp(_currentPosition.x, _currentPosition.y));
}

Egg::~Egg(void) { }
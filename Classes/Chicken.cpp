#include "Chicken.h"
#include "GameScene.h"

using namespace cocos2d;

//constructor
Chicken::Chicken(void) { }

Chicken::Chicken(GameScene * gameScene)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	_xMoveDistance = windowSize.height / 16; //16 because there are 16 lanes on the background image
	_yMoveDistance = _xMoveDistance;

	float originalWidth = 25;
	float originalHeight = 38;
	_sprite = CCSprite::create("small_chicken.png", CCRectMake(0, 0, originalWidth, originalHeight));

	float scaleRatio = (windowSize.height / 20) / _sprite->getContentSize().height; //20 because I want the image to be quite a bit smaller than the lane.
	//setScale only changes the size of the image, not the 'bounding box'
	_sprite->setScale(scaleRatio);

	float scaledWidth = originalWidth * scaleRatio;
	float scaledHeight = originalHeight * scaleRatio;
	//setContentSize changes the size of the 'bounding box' around the image
	_sprite->setContentSize(CCSize(scaledWidth, scaledHeight));

	_currentPosition.x = windowSize.width / 2;
	_currentPosition.y = (_sprite->getContentSize().height / 2);
	_sprite->setPosition(ccp(_currentPosition.x, _currentPosition.y));

	gameScene->addChild(_sprite);
}

Chicken::~Chicken(void) { }

CCSprite * Chicken::getSprite()
{
	return _sprite;
}

CCPoint Chicken::getPoint()
{
	return _currentPosition;
}

void Chicken::moveUp()
{
	_currentPosition.y += _yMoveDistance;
}

void Chicken::moveDown()
{
	_currentPosition.y -= _yMoveDistance;
}

void Chicken::moveLeft()
{
	_currentPosition.x -= _xMoveDistance;
}

void Chicken::moveRight()
{
	_currentPosition.x += _xMoveDistance;
}
#include "Chicken.h"
#include "GameLayer.h"

using namespace cocos2d;

//constructor
Chicken::Chicken(void) { }

Chicken::Chicken(GameLayer * gameLayer)
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

	_speed = .1;
	//_speed = 1;
	_isRiding = false;
	_isMoving = false;

	gameLayer->addChild(_sprite);
}

Chicken::~Chicken(void) { }

CCSprite * Chicken::getSprite()
{
	return _sprite;
}

CCPoint Chicken::getPoint()
{
	return _currentPosition;
	//return _sprite->getPosition();
}

void Chicken::moveUp()
{
	_currentPosition = _sprite->getPosition();
	float yPosition = this->getSprite()->getPositionY();
	_currentPosition.y = yPosition + _yMoveDistance;
	//_currentPosition.y += _yMoveDistance;
}

void Chicken::moveDown()
{
	_currentPosition = _sprite->getPosition();
	float yPosition = this->getSprite()->getPositionY();
	_currentPosition.y = yPosition - _yMoveDistance;
	//_currentPosition.y -= _yMoveDistance;
}

void Chicken::moveLeft()
{
	_currentPosition = _sprite->getPosition();
	float xPosition = this->getSprite()->getPositionX();
	_currentPosition.x = xPosition - _xMoveDistance;
	//_currentPosition.x -= _xMoveDistance;
}

void Chicken::moveRight()
{
	_currentPosition = _sprite->getPosition();
	float xPosition = this->getSprite()->getPositionX();
	_currentPosition.x = xPosition + _xMoveDistance;
	//_currentPosition.x += _xMoveDistance;
}

void Chicken::setSpeed(int speed)
{
	_speed = speed;
}

int Chicken::getSpeed()
{
	return _speed;
}

void Chicken::ride(Vehicle * vehicle)
{
	_isRiding = true;
}

void Chicken::setRiding(bool value)
{
	_isRiding = value;
}

bool Chicken::isRiding()
{
	return _isRiding;
}

void Chicken::endRide()
{
	_isRiding = false;
	_sprite->stopAllActions();
}

bool Chicken::isMoving()
{
	return _isMoving;
}

void Chicken::setMoving(bool value)
{
	_isMoving = value;
}


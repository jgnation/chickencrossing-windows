#include "Chicken.h"
#include "GameLayer.h"

using namespace cocos2d;

//constructor
Chicken::Chicken(void) { }

Chicken::Chicken(GameLayer * gameLayer)
{
	_gameLayer = gameLayer;
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

	_sprite->setPosition(ccp(windowSize.width / 2, _sprite->getContentSize().height / 2));

	_speed = .1;
	//_speed = 1;
	_isRiding = false;
	_isMoving = false;
	_logBeingRidden = NULL;

	gameLayer->addChild(_sprite, 1);
}

Chicken::~Chicken(void) { }

CCSprite * Chicken::getSprite()
{
	return _sprite;
}

void Chicken::moveUp()
{
	move(ccp(_sprite->getPositionX(), _sprite->getPositionY() + _yMoveDistance));
}

void Chicken::moveDown()
{
	move(ccp(_sprite->getPositionX(), _sprite->getPositionY() - _yMoveDistance));
}

void Chicken::moveLeft()
{
	move(ccp(_sprite->getPositionX() - _xMoveDistance, _sprite->getPositionY()));
}

void Chicken::moveRight()
{
	move(ccp(_sprite->getPositionX() + _xMoveDistance, _sprite->getPositionY()));
}

void Chicken::move(Point point)
{
	if (this->isRiding()) this->endRide();

	CCFiniteTimeAction* actionMove = CCMoveTo::create(this->getSpeed(), point);
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(Chicken::doneMoving));

	this->setMoving(true);
	this->getSprite()->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void Chicken::doneMoving(CCNode* sender)
{
	this->setMoving(false);
}

void Chicken::setSpeed(int speed)
{
	_speed = speed;
}

int Chicken::getSpeed()
{
	return _speed;
}

void Chicken::ride(Log * log)
{
	//initiate the riding animation
	int logSpeed = log->getSpeed();
	CCPoint destination = log->getDestination();

	float distance = ccpDistance(this->getSprite()->getPosition(), destination);
	float duration = distance / logSpeed;

	CCFiniteTimeAction* actionMove = CCMoveTo::create(duration, destination);
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(Chicken::spriteMoveFinished));
	this->getSprite()->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	_isRiding = true;
	_logBeingRidden = log;
}

Log * Chicken::getLogBeingRidden()
{
	return _logBeingRidden;
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
	_logBeingRidden = NULL;
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

void Chicken::die()
{
	this->endRide();	//adding this here fixed the bug where the game crashes when the riding chicken hits the edge of the screen

	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_sprite->setPosition(ccp(windowSize.width / 2, _sprite->getContentSize().height / 2));
	_isMoving = false;
}

void Chicken::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	_gameLayer->removeChild(sprite, true);
}
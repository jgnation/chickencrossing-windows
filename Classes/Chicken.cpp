#include "Chicken.h"
#include "GameLayer.h"

using namespace cocos2d;

Chicken* Chicken::create(GameLayer * gameLayer)
{
    Chicken *pGOL = new Chicken();
    if (pGOL && pGOL->init(gameLayer)) {
        pGOL->autorelease();
        return pGOL;
    }
    CC_SAFE_DELETE(pGOL);
    return NULL;
}

bool Chicken::init(GameLayer * gameLayer)
{
    bool bRet = false;
    do 
    {
		_gameLayer = gameLayer;
		CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

		_yMoveDistance = windowSize.height / 16; //16 because there are 16 lanes on the background image
		_xMoveDistance = _yMoveDistance; //TODO: scale this value?
		//_xMoveDistance = windowSize.width / 10;

		float originalWidth = 79;
		float originalHeight = 98;
		_sprite = CCSprite::create("chicken_xxsmall.png", CCRectMake(0, 0, originalWidth, originalHeight));
		_sprite->setAnchorPoint(ccp(0,0));

		float scaleRatioY = (windowSize.height / 17) / _sprite->getContentSize().height; //20 because I want the image to be quite a bit smaller than the lane.
		//setScale only changes the size of the image, not the 'bounding box'
		_sprite->setScale(scaleRatioY);

		float scaleRatioX = (windowSize.width / 12) / _sprite->getContentSize().width;
		_sprite->setScaleX(scaleRatioX);

		float scaledWidth = originalWidth * scaleRatioX;
		float scaledHeight = originalHeight * scaleRatioY;
		//setContentSize changes the size of the 'bounding box' around the image
		//_sprite->setContentSize(CCSize(scaledWidth, scaledHeight));

		_sprite->setPosition(ccp(windowSize.width / 2, Dimensions::getLanePixelValue(2)));

		_speed = .1;
		//_speed = 1;
		_isRiding = false;
		_isMoving = false;
		_logBeingRidden = NULL;

		gameLayer->addChild(_sprite, 1);

		this->createDeadChickenSprite();

		bRet = true;
    } while (0);

    return bRet;
}

Chicken::Chicken(void) { }

Chicken::~Chicken(void) { }

void Chicken::createDeadChickenSprite()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	float originalWidth = 100;
	float originalHeight = 85;
	_deadChickenSprite = CCSprite::create("deaths-head-xxsmall.png", CCRectMake(0, 0, originalWidth, originalHeight));
	_deadChickenSprite->setAnchorPoint(ccp(0,0));

	float scaleRatioY = (windowSize.height / 17) / _deadChickenSprite->getContentSize().height; //20 because I want the image to be quite a bit smaller than the lane.
	//setScale only changes the size of the image, not the 'bounding box'
	_deadChickenSprite->setScale(scaleRatioY);

	float scaleRatioX = (windowSize.width / 12) / _deadChickenSprite->getContentSize().width;
	_deadChickenSprite->setScaleX(scaleRatioX);

	float scaledWidth = originalWidth * scaleRatioX;
	float scaledHeight = originalHeight * scaleRatioY;
	//setContentSize changes the size of the 'bounding box' around the image
	//_deadChickenSprite->setContentSize(CCSize(scaledWidth, scaledHeight));
	
	_deadChickenSprite->setVisible(false);
	_gameLayer->addChild(_deadChickenSprite, 1);
}

CCSprite * Chicken::getSprite()
{
	return _sprite;
}

void Chicken::moveUp()
{
	Point point = ccp(_sprite->getPositionX(), _sprite->getPositionY() + _yMoveDistance);
	if (Dimensions::moveIsInPlayableArea(point, this))
	{
		move(point);
	}
	else
	{
		this->setMoving(false); //this is set because setMoving(true) is called in GameLayer
		//maybe GameLayer shouldn't be calling that?
	}
}

void Chicken::moveDown()
{
	Point point = ccp(_sprite->getPositionX(), _sprite->getPositionY() - _yMoveDistance);
	if (Dimensions::moveIsInPlayableArea(point, this))
	{
		move(point);
	}
	else
	{
		this->setMoving(false); //this is set because setMoving(true) is called in GameLayer
		//maybe GameLayer shouldn't be calling that?
	}
}

void Chicken::moveLeft()
{
	Point point = ccp(_sprite->getPositionX() - _xMoveDistance, _sprite->getPositionY());
	if (Dimensions::moveIsInPlayableArea(point, this))
	{
		move(point);
		//if moving left and not in playable area, I'm pretty sure I can just set the chicken at the left edge of the screen.
	}
	else
	{
		move(ccp(0, _sprite->getPositionY()));
		//this->setMoving(false); //this is set because setMoving(true) is called in GameLayer
		//maybe GameLayer shouldn't be calling that?
	}
}

void Chicken::moveRight()
{
	Point point = ccp(_sprite->getPositionX() + _xMoveDistance, _sprite->getPositionY());
	if (Dimensions::moveIsInPlayableArea(point, this))
	{
		move(point);
	}
	else
	{
		CCSize windowSize = CCDirector::sharedDirector()->getWinSize();	
		float xPos = windowSize.width - _sprite->getBoundingBox().size.width;
		move(ccp(xPos, _sprite->getPositionY()));
		//this->setMoving(false); //this is set because setMoving(true) is called in GameLayer
		//maybe GameLayer shouldn't be calling that?
	}
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

void Chicken::reset()
{
	this->endRide(); //adding this here fixed the bug where the game crashes when the riding chicken hits the edge of the screen
	_isMoving = false;

	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_sprite->setPosition(ccp(windowSize.width / 2, Dimensions::getLanePixelValue(2)));
}

void Chicken::die(bool resurrect)
{
	Point curentPosition = _sprite->getPosition();
	this->reset();

	_deadChickenSprite->setPosition(curentPosition);
	_deadChickenSprite->setVisible(true);
	_sprite->setVisible(false);

	_deadChickenSprite->setOpacity(255);
	CCFadeTo* fadeOut = CCFadeTo::create(1.0, 0);
	CCFiniteTimeAction * actionFade = CCFadeTo::create(1.0, 0);

	CCFiniteTimeAction* actionFadeDone;
	if (resurrect)
		actionFadeDone = CCCallFuncN::create(this, callfuncN_selector(Chicken::resurrectChicken));
	else
		actionFadeDone = CCCallFuncN::create(this, callfuncN_selector(Chicken::noChickenResurrection));

	_deadChickenSprite->runAction(CCSequence::create(actionFade, actionFadeDone, NULL));
}

void Chicken::resurrectChicken(cocos2d::CCNode* sender)
{
	_deadChickenSprite->setVisible(false);
	_sprite->setVisible(true);
}

void Chicken::noChickenResurrection(cocos2d::CCNode* sender)
{
	_deadChickenSprite->setVisible(false);
}

void Chicken::spriteMoveFinished(CCNode* sender)
{
	//TODO: I don't think this function is ever called, due to the chicken being killed when hitting the edge of the screen
	CCSprite *sprite = (CCSprite *)sender;
	_gameLayer->removeChild(sprite, true);
}
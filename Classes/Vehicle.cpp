#include "Vehicle.h"
#include "GameLayer.h"

using namespace cocos2d;

Vehicle::Vehicle(void)
{
}

Vehicle::~Vehicle(void)
{
}

int Vehicle::getSpeed()
{
	return _speed;
}

void Vehicle::setSpeed(int speed)
{
	_speed = speed;
}

CCPoint Vehicle::getOrigin()
{
	return _origin;
}

CCPoint Vehicle::getDestination()
{
	return _destination;
}

void Vehicle::setDestination(cocos2d::CCPoint destination)
{
	_destination = destination;
}

void Vehicle::setMovementAction(CCFiniteTimeAction * action)
{
	_movementAction = action;
}

CCFiniteTimeAction * Vehicle::getMovementAction()
{
	return _movementAction;
}

void Vehicle::move()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float distance = 0;
	if (_destination.x < 0)
	{
		//vehicle is moving left
		distance = ccpDistance(ccp(winSize.width, _destination.y), _destination);
	}
	else //destination.x > winSize.width
	{
		//vehicle is moving right
		distance = ccpDistance(ccp(0, _destination.y), _destination);
	}

	float duration = distance / _speed;
	CCFiniteTimeAction * actionMove = CCMoveTo::create(duration, _destination);
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::spriteMoveFinished3));
	this->getSprite()->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	
	/*CCFadeTo* fadeOut = CCFadeTo::create(0.5, 0);
	CCFadeTo* stayHidden = CCFadeTo::create(2.0, 0);
	CCFadeTo* fadeIn = CCFadeTo::create(0.5, 255);
	CCArray * arrayOfAction = CCArray::create();
	arrayOfAction->addObject(fadeOut);
	arrayOfAction->addObject(stayHidden);
	arrayOfAction->addObject(fadeIn);
	CCSequence* pulseSequence = CCSequence::create(arrayOfAction);
	CCRepeatForever* repeat = CCRepeatForever::create(pulseSequence);
	this->getSprite()->runAction(repeat);*/

	//if I call a callback in GameLayer, then I don't have to have a reference to the GameLayer object in this clas
}

void Vehicle::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	//_gameLayer->removeChild(sprite, true);

	delete this;
}
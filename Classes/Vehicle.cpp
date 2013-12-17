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
}

void Vehicle::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	//_gameLayer->removeChild(sprite, true);

	delete this;
}
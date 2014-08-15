#ifndef VEHICLE_H
#define VEHICLE_H

#include "SpriteContainer.h"

class Vehicle : public SpriteContainer
{
protected:
	int _speed;
	cocos2d::CCPoint _origin;
	cocos2d::CCPoint _destination;
	cocos2d::CCFiniteTimeAction * _movementAction;
	//GameLayer * _gameLayer;
public:
	Vehicle(void);
	~Vehicle(void);
	virtual int getSpeed();
	void setSpeed(int speed);
	cocos2d::CCPoint getOrigin();
	cocos2d::CCPoint getDestination();
	void setDestination(cocos2d::CCPoint destination);
	void setMovementAction(cocos2d::CCFiniteTimeAction * action);
	cocos2d::CCFiniteTimeAction * getMovementAction();
	virtual void move();
	void spriteMoveFinished(cocos2d::CCNode * sender);
};

#endif
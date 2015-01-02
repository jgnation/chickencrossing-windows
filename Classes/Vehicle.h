#ifndef VEHICLE_H
#define VEHICLE_H

#include "SpriteContainer.h"

class Vehicle : public SpriteContainer
{
protected:
	int _speed;
	float _duration;
	bool _isDoneMoving;
	cocos2d::CCPoint _origin;
	cocos2d::CCPoint _destination;
	cocos2d::CCFiniteTimeAction * _movementAction;
public:
	Vehicle(void);
	~Vehicle(void);

	virtual int getSpeed(); //TODO: should I make this a friend function to share with Chicken?
	virtual float getDuration();
	bool isDoneMoving();
	void setDuration(float duration);
	cocos2d::CCPoint getOrigin();
	cocos2d::CCPoint getDestination();
	void setDestination(cocos2d::CCPoint destination);
	void setMovementAction(cocos2d::CCFiniteTimeAction * action);
	cocos2d::CCFiniteTimeAction * getMovementAction();
	virtual void move();
	void spriteMoveFinished(cocos2d::CCNode * sender);
	void finishMovement();
};

#endif
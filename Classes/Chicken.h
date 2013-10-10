#ifndef CHICKEN_H
#define CHICKEN_H

#include "cocos2d.h"
#include "SpriteContainer.h"
#include "Vehicle.h"

class GameLayer;	//forward declaration
class Chicken : public SpriteContainer
{
private:
	cocos2d::CCPoint _currentPosition;
	int _yMoveDistance;
	int _xMoveDistance;
	int _speed;
	bool _isRiding;
	bool _isMoving;
public:
	Chicken(void);
	Chicken(GameLayer* gameScene);
	~Chicken(void);

	cocos2d::CCSprite * getSprite();
	cocos2d::CCPoint getPoint();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void setSpeed(int speed);
	int getSpeed();
	void ride(Vehicle * vehicle);
	void setRiding(bool value);
	bool isRiding();
	void endRide();
	void setMoving(bool value);
	bool isMoving();
};

#endif
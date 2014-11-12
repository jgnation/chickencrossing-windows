#ifndef CHICKEN_H
#define CHICKEN_H

#include "cocos2d.h"
#include "SpriteContainer.h"
#include "Log.h"
#include "Dimensions.h"

class GameLayer;	//forward declaration
class Chicken : public SpriteContainer
{
private:
	cocos2d::CCSprite * _deadChickenSprite;

	Dimensions * _dimensions;
	int _yMoveDistance;
	int _xMoveDistance;
	int _speed;
	bool _isRiding;
	bool _isMoving;
	GameLayer *  _gameLayer;
	Log *_logBeingRidden;

	void move(cocos2d::Point point);
	void doneMoving(cocos2d::CCNode* sender);
	void createDeadChickenSprite();
public:
	Chicken(void);
	Chicken(GameLayer* gameScene);
	~Chicken(void);

	cocos2d::CCSprite * getSprite();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void setSpeed(int speed);
	int getSpeed();
	void ride(Log * log);
	void setRiding(bool value);
	bool isRiding();
	void endRide();
	void setMoving(bool value);
	bool isMoving();
	void die(bool resurrect);
	void reset();
	Log * getLogBeingRidden();

	void spriteMoveFinished(cocos2d::CCNode* sender);
	void resurrectChicken(cocos2d::CCNode* sender);
	void noChickenResurrection(cocos2d::CCNode* sender);
};

#endif
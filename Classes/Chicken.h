#ifndef CHICKEN_H
#define CHICKEN_H

#include "cocos2d.h"

class GameScene;	//forward declaration
class Chicken
{
private:
	cocos2d::CCSprite * _chickenSprite;
	cocos2d::CCPoint _currentPosition;
	int _yMoveDistance;
	int _xMoveDistance;
public:
	Chicken(void);
	Chicken(GameScene* gameScene);
	~Chicken(void);

	cocos2d::CCSprite * getSprite();
	cocos2d::CCPoint getPoint();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
};

#endif
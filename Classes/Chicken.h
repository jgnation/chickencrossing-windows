#ifndef CHICKEN_H
#define CHICKEN_H

#include "cocos2d.h"
#include "SpriteContainer.h"

class GameLayer;	//forward declaration
class Chicken : public SpriteContainer
{
private:
	cocos2d::CCPoint _currentPosition;
	int _yMoveDistance;
	int _xMoveDistance;
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
};

#endif
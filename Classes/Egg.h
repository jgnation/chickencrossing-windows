#ifndef EGG_H
#define EGG_H

#include "cocos2d.h"
#include "SpriteContainer.h"

class Egg : public SpriteContainer
{
private:
	cocos2d::CCPoint _currentPosition;
public:
	Egg(void);
	~Egg(void);
	void setPosition(float x, float y);
};

#endif
#ifndef SPRITECONTAINER_H
#define SPRITECONTAINER_H

#include "cocos2d.h"

class SpriteContainer
{
protected:
	cocos2d::CCSprite * _sprite;
	cocos2d::CCPoint _origin;
	cocos2d::CCPoint _destination;
public:
	SpriteContainer(void);
	~SpriteContainer(void);
	cocos2d::CCSprite * getSprite();
	cocos2d::CCPoint getOrigin();
	cocos2d::CCPoint getDestination();
};

#endif

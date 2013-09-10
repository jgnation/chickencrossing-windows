#ifndef SPRITECONTAINER_H
#define SPRITECONTAINER_H

#include "cocos2d.h"

class SpriteContainer
{
protected:
	cocos2d::CCSprite * _sprite;

public:
	SpriteContainer(void);
	~SpriteContainer(void);
	cocos2d::CCSprite * getSprite();
};

#endif

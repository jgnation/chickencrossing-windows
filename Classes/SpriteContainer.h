#ifndef SPRITECONTAINER_H
#define SPRITECONTAINER_H

#include "cocos2d.h"

class SpriteContainer : public cocos2d::CCNode
{
protected:
	cocos2d::CCSprite * _sprite;

public:
	SpriteContainer(void);
	~SpriteContainer(void);
	cocos2d::CCSprite * getSprite();
	bool intersectsSprite(SpriteContainer * sprite);
};

#endif

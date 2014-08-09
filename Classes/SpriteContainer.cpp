#include "SpriteContainer.h"

using namespace cocos2d;

SpriteContainer::SpriteContainer(void)
{
}

CCSprite * SpriteContainer::getSprite()
{
	return _sprite;
}

SpriteContainer::~SpriteContainer(void)
{
}

bool SpriteContainer::intersectsSprite(SpriteContainer * container)
{
	if (container->getSprite()->getOpacity() == 0)
	{
		return false;
	}
	else
	{
		/*
		I had to taint this function due to the inconsistent and ridiculous ways that cocos2d-x deals with sprites.
		Regardless of anchor point, cocos2dx will flip a sprite around the y axis when executing:
		vehicleSprite->setScaleX(vehicleSprite->getScaleX() * -1.f); (e.g. in the Lane class)

		As long as _vehicles_ are provided as the parameter to this function, it will work.
		*/
		CCRect thisRect = CCRectMake(
			_sprite->getPosition().x,
			_sprite->getPosition().y,
			_sprite->getContentSize().width,
			_sprite->getContentSize().height);

		CCRect spriteRect;
		if (container->getSprite()->getScaleX() > 0)
		{
			spriteRect = CCRectMake(
				container->getSprite()->getPosition().x,
				container->getSprite()->getPosition().y,
				container->getSprite()->getContentSize().width,
				container->getSprite()->getContentSize().height);
		}
		else
		{
			spriteRect = CCRectMake(
				container->getSprite()->getPosition().x - (container->getSprite()->getContentSize().width),
				container->getSprite()->getPosition().y,
				container->getSprite()->getContentSize().width,
				container->getSprite()->getContentSize().height);
		}

		return thisRect.intersectsRect(spriteRect);	
	}
}

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
		CCRect thisRect = CCRectMake(
			_sprite->getPosition().x - (_sprite->getContentSize().width / 2),
			_sprite->getPosition().y - (_sprite->getContentSize().height / 2),
			_sprite->getContentSize().width,
			_sprite->getContentSize().height);

		CCRect spriteRect = CCRectMake(
			container->getSprite()->getPosition().x - (container->getSprite()->getContentSize().width / 2),
			container->getSprite()->getPosition().y - (container->getSprite()->getContentSize().height / 2),
			container->getSprite()->getContentSize().width,
			container->getSprite()->getContentSize().height);

		return thisRect.intersectsRect(spriteRect);	
	}
}

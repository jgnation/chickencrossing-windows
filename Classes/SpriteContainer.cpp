#include "SpriteContainer.h"

using namespace cocos2d;

SpriteContainer::SpriteContainer(void)
{
}

CCSprite * SpriteContainer::getSprite()
{
	return _sprite;
}

CCPoint SpriteContainer::getOrigin()
{
	return _origin;
}

CCPoint SpriteContainer::getDestination()
{
	return _destination;
}

SpriteContainer::~SpriteContainer(void)
{
}

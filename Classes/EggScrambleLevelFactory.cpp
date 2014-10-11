#include "EggScrambleLevelFactory.h"
#include "EggScrambleLevel.h"

using namespace cocos2d;


EggScrambleLevelFactory::EggScrambleLevelFactory(void)
{
}


EggScrambleLevelFactory::~EggScrambleLevelFactory(void)
{
}

Level * EggScrambleLevelFactory::createLevel(CCDictionary * levelData)
{
	return new EggScrambleLevel(levelData);
}

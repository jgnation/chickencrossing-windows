#include "MainModeLevelFactory.h"
#include "MainModeLevel.h"

using namespace cocos2d;

MainModeLevelFactory::MainModeLevelFactory(void)
{
}


MainModeLevelFactory::~MainModeLevelFactory(void)
{
}

Level * MainModeLevelFactory::createLevel(CCDictionary * levelData)
{
	return new MainModeLevel(levelData);
}

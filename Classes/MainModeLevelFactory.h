#ifndef MAIN_MODE_LEVEL_FACTORY_H
#define MAIN_MODE_LEVEL_FACTORY_H

#include "LevelFactory.h"
#include "Level.h"
#include "cocos2d.h"

class MainModeLevelFactory : public LevelFactory
{
public:
	MainModeLevelFactory(void);
	~MainModeLevelFactory(void);
	Level * createLevel(cocos2d::CCDictionary * levelData);
};

#endif


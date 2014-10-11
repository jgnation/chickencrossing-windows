#ifndef EGG_SCRAMBLE_LEVEL_FACTORY_H
#define EGG_SCRAMBLE_LEVEL_FACTORY_H

#include "LevelFactory.h"
#include "Level.h"
#include "cocos2d.h"

class EggScrambleLevelFactory : public LevelFactory
{
public:
	EggScrambleLevelFactory(void);
	~EggScrambleLevelFactory(void);
	Level * createLevel(cocos2d::CCDictionary * levelData);
};

#endif


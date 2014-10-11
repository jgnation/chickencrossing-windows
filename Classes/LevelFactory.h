#ifndef LEVEL_FACTORY_H
#define LEVEL_FACTORY_H

//#include "Level.h"
#include "cocos2d.h"

class Level;
class LevelFactory
{
public:
	LevelFactory(void);
	~LevelFactory(void);
	virtual Level * createLevel(cocos2d::CCDictionary * levelData) = 0;
};

#endif


#ifndef __LEVELMANAGER_H__
#define __LEVELMANAGER_H__
 
#include "cocos2d.h"
#include "Background.h"
#include "Level.h"
#include "LevelFactory.h"
 
using namespace cocos2d;

class Level; // <- why is this necessary?  Maybe it has to do with the 'friend' thing
class LevelFactory;
class LevelManager
{
public:
	LevelManager(LevelFactory * factory);
	~LevelManager();

	Level * getLevel(int levelNumber);
	int mapLevelNumberToLevelPList(int levelNumber);

protected:
    Background * _background;
	CCDictionary * _levelData;
	CCDictionary * _levels;
	int _numOfLevels;
private:
	LevelFactory * _levelFactory;
};
 
#endif // __LEVELMANAGER_H__
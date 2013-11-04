#ifndef __LEVELMANAGER_H__
#define __LEVELMANAGER_H__
 
#include "cocos2d.h"
#include "Background.h"
#include "Level.h"
 
using namespace cocos2d;

class Level; // <- why is this necessary?  Maybe it has to do with the 'friend' thing
class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	Level * getLevel(int levelNumber);

protected:
    Background * _background;
	CCDictionary * _levelData;
	CCDictionary * _levels;
};
 
#endif // __LEVELMANAGER_H__
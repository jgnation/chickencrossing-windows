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
	CCArray * _levels;

	/*
	 For some reason the _lanes map had to be declared BELOW the enum, otherwise it was 'undefined'.  Forward declaration wouldn't work.
	 It caused a strange error in Level1.cpp.
	*/

};
 
#endif // __LEVELMANAGER_H__
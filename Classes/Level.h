#ifndef LEVEL_H
#define LEVEL_H

#include "LevelManager.h"
#include "cocos2d.h"
#include "Background.h"

class Level
{
private:
	Level(cocos2d::CCDictionary * levelData);
	~Level(void);
	friend class LevelManager;	//only the LevelManager can instantiate this class

	cocos2d::CCDictionary * _levelData;
	Background * _background;
public:
	enum LaneType { ROAD, WATER, REST, INVALID };

	Background * getBackground();
	Level::LaneType getLaneType(int laneNumber);
};

#endif // LEVEL_H
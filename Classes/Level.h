#ifndef LEVEL_H
#define LEVEL_H

#include "LevelManager.h"
#include "cocos2d.h"
#include "Background.h"
#include "Lane.h"

class Level
{
private:
	Level(cocos2d::CCDictionary * levelData);
	~Level(void);
	friend class LevelManager;	//only the LevelManager can instantiate this class


	cocos2d::CCDictionary * _levelData;
	Background * _background;
	std::vector<Lane *> _lanes;
public:
	enum LaneType { ROAD, WATER, REST, INVALID };

	Background * getBackground();
	Level::LaneType getLaneType(int laneNumber);
	Lane * getLane(int laneNumber);
	std::vector<Lane *> getLanes();
};

#endif // LEVEL_H
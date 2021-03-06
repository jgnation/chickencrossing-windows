#ifndef LEVEL_H
#define LEVEL_H

#include "LevelManager.h"
#include "cocos2d.h"
#include "Background.h"
#include "Lane.h"

class Level
{
protected:

	cocos2d::CCDictionary * _levelData;

	virtual int getMaxRoadInterval() = 0;
	virtual int getMinRoadInterval() = 0;
	virtual int getMinWaterInterval() = 0;
	virtual int getMaxWaterInterval() = 0;
	virtual float getMinStartDurationRoad() = 0;
	virtual float getMaxStartDurationRoad() = 0;
	virtual float getMinStartDurationWater() = 0;
	virtual float getMaxStartDurationWater() = 0;
	virtual Lane * createNewLane(int laneNumber, Lane::LaneType laneType, int interval, float duration, std::vector<std::string> vehicles) = 0;

	Level(cocos2d::CCDictionary * levelData);
private:
	friend class LevelManager;	//only the LevelManager can instantiate this class

	Background * _background;
	std::vector<Lane *> _lanes;

public:
	virtual ~Level(void);
	void init();
	Background * getBackground();
	Lane::LaneType getLaneType(int laneNumber);
	Lane * getLane(int laneNumber);
	std::vector<Lane *> getLanes();
	int getRandomValidLaneNumber();
};

#endif // LEVEL_H
#ifndef MAIN_MODE_LEVEL_H
#define MAIN_MODE_LEVEL_H

#include "Level.h"
#include "Lane.h"
#include "cocos2d.h"

class MainModeLevel : public Level
{
protected:
	int getMaxRoadInterval();
	int getMinRoadInterval();
	int getMinWaterInterval();
	int getMaxWaterInterval();
	float getMinStartDurationRoad();
	float getMaxStartDurationRoad();
	float getMinStartDurationWater();
	float getMaxStartDurationWater();
	Lane * createNewLane(int laneNumber, Lane::LaneType laneType, int interval, float duration, std::vector<std::string> vehicles);

private:
	
	cocos2d::CCDictionary * _mainModeData;
public:
	MainModeLevel(cocos2d::CCDictionary * levelData);
	~MainModeLevel(void);
};

#endif


#ifndef EGG_SCRAMBLE_LEVEL_H
#define EGG_SCRAMBLE_LEVEL_H

#include "Level.h"
#include "Lane.h"
#include "cocos2d.h"

class EggScrambleLevel : public Level
{
protected:
		int getMaxRoadInterval();
	int getMinRoadInterval();
	int getMinWaterInterval();
	int getMaxWaterInterval();
	float getMinStartDuration();
	float getMaxStartDuration();
	Lane * createNewLane(int laneNumber, Lane::LaneType laneType, int interval, float duration, std::vector<std::string> vehicles);
private:


	cocos2d::CCDictionary * _eggScrambleData;
public:
	EggScrambleLevel(cocos2d::CCDictionary * levelData);
	~EggScrambleLevel(void);
};

#endif


#include "EggScrambleLevel.h"
#include "AcceleratingLane.h"

EggScrambleLevel::EggScrambleLevel(CCDictionary * levelData) : Level(levelData)
{
	_eggScrambleData = (CCDictionary*) levelData->objectForKey("EggScramble");
}

EggScrambleLevel::~EggScrambleLevel(void)
{
	//TODO: for some reason, releasing this causes a runtime heap deallocation error
	//Maybe the _levelData->release() in Level takes care of this?
	//_eggScrambleData->release();
}

int EggScrambleLevel::getMaxRoadInterval()
{
	return _eggScrambleData->valueForKey("MaxRoadInterval")->intValue();
}

int EggScrambleLevel::getMinRoadInterval()
{
	return _eggScrambleData->valueForKey("MinRoadInterval")->intValue();
}

int EggScrambleLevel::getMinWaterInterval()
{
	return _eggScrambleData->valueForKey("MinWaterInterval")->intValue();
}

int EggScrambleLevel::getMaxWaterInterval()
{
	return _eggScrambleData->valueForKey("MaxWaterInterval")->intValue();
}

float EggScrambleLevel::getMinStartDurationRoad()
{
	return _eggScrambleData->valueForKey("MinStartDurationRoad")->floatValue();
}

float EggScrambleLevel::getMaxStartDurationRoad()
{
	return _eggScrambleData->valueForKey("MaxStartDurationRoad")->floatValue();
}

float EggScrambleLevel::getMinStartDurationWater()
{
	return _eggScrambleData->valueForKey("MinStartDurationWater")->floatValue();
}

float EggScrambleLevel::getMaxStartDurationWater()
{
	return _eggScrambleData->valueForKey("MaxStartDurationWater")->floatValue();
}

Lane * EggScrambleLevel::createNewLane(int laneNumber, Lane::LaneType laneType, int interval, float duration, std::vector<std::string> vehicles)
{
	float maxDuration = _eggScrambleData->valueForKey("MaxDuration")->floatValue();
	float minDuration = _eggScrambleData->valueForKey("MinDuration")->floatValue();
	return new AcceleratingLane(laneNumber, laneType, interval, duration, maxDuration, minDuration, vehicles);
}

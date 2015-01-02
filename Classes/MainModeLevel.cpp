#include "MainModeLevel.h"

MainModeLevel::MainModeLevel(CCDictionary * levelData) : Level(levelData)
{
	_mainModeData = (CCDictionary*) levelData->objectForKey("MainMode");
}

int MainModeLevel::getMaxRoadInterval()
{
	return _mainModeData->valueForKey("MaxRoadInterval")->intValue();
}

int MainModeLevel::getMinRoadInterval()
{
	return _mainModeData->valueForKey("MinRoadInterval")->intValue();
}

int MainModeLevel::getMinWaterInterval()
{
	return _mainModeData->valueForKey("MinWaterInterval")->intValue();
}

int MainModeLevel::getMaxWaterInterval()
{
	return _mainModeData->valueForKey("MaxWaterInterval")->intValue();
}

float MainModeLevel::getMinStartDuration()
{
	return _mainModeData->valueForKey("MinStartDuration")->floatValue();
}

float MainModeLevel::getMaxStartDuration()
{
	return _mainModeData->valueForKey("MaxStartDuration")->floatValue();
}

Lane * MainModeLevel::createNewLane(int laneNumber, Lane::LaneType laneType, int interval, float duration, std::vector<std::string> vehicles)
{
	return new Lane(laneNumber, laneType, interval, duration, vehicles);
}

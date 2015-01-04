#include "MainModeLevel.h"

MainModeLevel::MainModeLevel(CCDictionary * levelData) : Level(levelData)
{
	_mainModeData = (CCDictionary*) levelData->objectForKey("MainMode");
}

MainModeLevel::~MainModeLevel(void)
{
	//TODO: for some reason, releasing this causes a runtime heap deallocation error
	//Maybe the _levelData->release() in Level takes care of this?
	//_mainModeData->release();
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

float MainModeLevel::getMinStartDurationRoad()
{
	return _mainModeData->valueForKey("MinStartDurationRoad")->floatValue();
}

float MainModeLevel::getMaxStartDurationRoad()
{
	return _mainModeData->valueForKey("MaxStartDurationRoad")->floatValue();
}

float MainModeLevel::getMinStartDurationWater()
{
	return _mainModeData->valueForKey("MinStartDurationWater")->floatValue();
}

float MainModeLevel::getMaxStartDurationWater()
{
	return _mainModeData->valueForKey("MaxStartDurationWater")->floatValue();
}

Lane * MainModeLevel::createNewLane(int laneNumber, Lane::LaneType laneType, int interval, float duration, std::vector<std::string> vehicles)
{
	return new Lane(laneNumber, laneType, interval, duration, vehicles);
}

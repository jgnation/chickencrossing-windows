#include "Level.h"

using namespace cocos2d;

Level::Level(CCDictionary * levelData)
{
	_levelData = levelData;
	_background = new Background(_levelData->valueForKey("Background")->getCString());
}

Background * Level::getBackground()
{
	return _background;
}

Level::LaneType Level::getLaneType(int laneNumber)
{
	laneNumber--; //the index of the items in the file are 1 less than I am using in the program
	//I am using 'natural indeces'

	CCArray * lanes = (CCArray *) _levelData->objectForKey("Lanes");
	CCDictionary * lane = (CCDictionary *) lanes->objectAtIndex(laneNumber);
	CCString * laneType = (CCString *) lane->objectForKey("Type");
	std::string laneTypeString = laneType->getCString();

	LaneType laneEnumType;
	if (laneTypeString == "INVALID")
		laneEnumType = Level::LaneType::INVALID;
	else if (laneTypeString == "REST")
		laneEnumType = Level::LaneType::REST;
	else if (laneTypeString == "ROAD")
		laneEnumType = Level::LaneType::ROAD;
	else // == WATER
		laneEnumType = Level::LaneType::WATER;

	return laneEnumType;
}
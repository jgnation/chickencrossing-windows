#include "Level.h"

using namespace cocos2d;

Level::Level(void)
{
	std::string levelsFileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("levels.plist");
	CCArray * levels = CCArray::createWithContentsOfFileThreadSafe(levelsFileName.c_str());
	levels->retain();

	_levelData = (CCDictionary *) levels->objectAtIndex(0);

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

	CCString * laneType = (CCString *) lanes->objectAtIndex(laneNumber);
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
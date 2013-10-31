#include "LevelManager.h"

using namespace cocos2d;

LevelManager::LevelManager(void)
{
	std::string levelsFileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("levels.plist");
	_levels = CCArray::createWithContentsOfFileThreadSafe(levelsFileName.c_str());
	_levels->retain();

	_levelData = (CCDictionary *) _levels->objectAtIndex(0);

	_background = new Background(_levelData->valueForKey("Background")->getCString());
}


/*Background * LevelManager::getBackground()
{
	return _background;
}

LevelManager::LaneType LevelManager::getLaneType(int laneNumber)
{
	laneNumber--; //the index of the items in the file are 1 less than I am using in the program
	//I am using 'natural indeces'

	CCArray * lanes = (CCArray *) _levelData->objectForKey("Lanes");

	CCString * laneType = (CCString *) lanes->objectAtIndex(laneNumber);
	std::string laneTypeString = laneType->getCString();

	LaneType laneEnumType;
	if (laneTypeString == "INVALID")
		laneEnumType = LevelManager::LaneType::INVALID;
	else if (laneTypeString == "REST")
		laneEnumType = LevelManager::LaneType::REST;
	else if (laneTypeString == "ROAD")
		laneEnumType = LevelManager::LaneType::ROAD;
	else // == WATER
		laneEnumType = LevelManager::LaneType::WATER;

	return laneEnumType;
}*/

Level * LevelManager::getLevel(int levelNumber)
{
	return new Level((CCDictionary *) _levels->objectAtIndex(levelNumber));
}
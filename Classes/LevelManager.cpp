#include "LevelManager.h"
#include "GameFunctions.h"
//#include <string>

using namespace cocos2d;

LevelManager::LevelManager()
{
	std::string levelsFileName = CCFileUtils::sharedFileUtils()->fullPathForFilename("levels.plist");
	_levels = CCDictionary::createWithContentsOfFileThreadSafe(levelsFileName.c_str());
	_levels->retain();

	_numOfLevels = _levels->count();
}

Level * LevelManager::getLevel(int levelNumber)
{
	levelNumber = this->mapLevelNumberToLevelPList(levelNumber);

	std::string fileName = _levels->valueForKey(GameFunctions::to_string(levelNumber))->getCString();
	std::string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
	return new Level(CCDictionary::createWithContentsOfFileThreadSafe(filePath.c_str()));
}

int LevelManager::mapLevelNumberToLevelPList(int levelNumber)
{
	if (levelNumber % _numOfLevels == 0)
	{
		return _numOfLevels;
	}
	else
	{
		return levelNumber % _numOfLevels;
	}
}
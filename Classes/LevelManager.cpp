#include "LevelManager.h"

using namespace cocos2d;

LevelManager::LevelManager()
{
	//std::string levelsFileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("levels.plist");
	//_levels = CCDictionary::createWithContentsOfFileThreadSafe(levelsFileName.c_str());
	//_levels->retain();
}

Level * LevelManager::getLevel(int levelNumber)
{
	//return new Level((CCDictionary *) _levels->objectForKey(std::to_string(levelNumber)));
	std::string fileName = std::string("level_") + std::to_string(levelNumber) + ".plist";
	std::string levelsFileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fileName.c_str());
	return new Level(CCDictionary::createWithContentsOfFileThreadSafe(levelsFileName.c_str()));
}
#include "LevelManager.h"

using namespace cocos2d;

LevelManager::LevelManager(void)
{
	std::string levelsFileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("levels.plist");
	_levels = CCDictionary::createWithContentsOfFileThreadSafe(levelsFileName.c_str());
	_levels->retain();
}

Level * LevelManager::getLevel(int levelNumber)
{
	return new Level((CCDictionary *) _levels->objectForKey(std::to_string(levelNumber)));
}
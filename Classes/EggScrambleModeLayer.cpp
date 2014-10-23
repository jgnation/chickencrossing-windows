#include "EggScrambleModeLayer.h"
#include "Lane.h"
#include "Level.h"
#include "GameFunctions.h"
#include "EggScrambleLevelFactory.h"
#include "AcceleratingLane.h"

using namespace cocos2d;

EggScrambleModeLayer::EggScrambleModeLayer(void)
{
}


EggScrambleModeLayer::~EggScrambleModeLayer(void)
{
}

CCScene* EggScrambleModeLayer::scene(int levelNumber)
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameLayer *layer = EggScrambleModeLayer::create(levelNumber);
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

EggScrambleModeLayer* EggScrambleModeLayer::create(int levelNumber)
{
    EggScrambleModeLayer *pGOL = new EggScrambleModeLayer();
    if (pGOL && pGOL->init(levelNumber)) {
        pGOL->autorelease();
        return pGOL;
    }
    CC_SAFE_DELETE(pGOL);
    return NULL;
}

bool EggScrambleModeLayer::init(int levelNumber)
{
	//http://www.dreamincode.net/forums/topic/243971-do-while0%3B/
	//above is an explanation of do...while(0)
    bool bRet = false;
    do 
    {
		_levelNumber = levelNumber;
		_levelManager = new LevelManager(new EggScrambleLevelFactory(), "esm_levels.plist");
		_waveNumber = 1;
		_nextWaveScore = calculateNextLevelScore(_waveNumber);

        CC_BREAK_IF(! GameLayer::init());

        bRet = true;
    } while (0);

    return bRet;
}

void EggScrambleModeLayer::initialChecks()
{
	if (_score >= _nextWaveScore)
	{		
		_waveNumber++;
		_nextWaveScore = calculateNextLevelScore(_waveNumber);

		std::vector<Lane *> lanes = _level->getLanes();

		for(std::vector<Lane *>::iterator it = lanes.begin(); it != lanes.end(); ++it) 
		{
			/*
			I was initially getting the following error when trying to downcast the Lane to an Accelerating Lane:
			"the operand of runtime dynamic_cast must have a polymorphic class type"
			The operand, in this case, is *it, which is a Lane*.  To make the class polymorphic, I simply
			made one of the methods in Lane virtual (even though I have no intention of overriding it).
			*/
			AcceleratingLane * lane = dynamic_cast<AcceleratingLane *>(*it);

			Lane::LaneType laneType = lane->getLaneType();
			if (laneType == Lane::LaneType::ROAD || laneType == Lane::LaneType::WATER)
			{
				lane->increaseSpeed();
			}		
		}
	}
}

std::vector<TopScore> EggScrambleModeLayer::checkHighScores()
{
	//all of this saving functionality should be pulled into another class
	std::vector<TopScore> highScores;
	highScores.push_back(TopScore(CCUserDefault::sharedUserDefault()->getIntegerForKey("esm_place_1"), false));
	highScores.push_back(TopScore(CCUserDefault::sharedUserDefault()->getIntegerForKey("esm_place_2"), false));
	highScores.push_back(TopScore(CCUserDefault::sharedUserDefault()->getIntegerForKey("esm_place_3"), false));
	highScores.push_back(TopScore(CCUserDefault::sharedUserDefault()->getIntegerForKey("esm_place_4"), false));
	highScores.push_back(TopScore(CCUserDefault::sharedUserDefault()->getIntegerForKey("esm_place_5"), false));

	bool topScore = false;
	for (int i = 0; i < highScores.size(); i++)
	{
		if (_score > highScores[i].getScore())
		{
			highScores.emplace(highScores.begin() + i, TopScore(_score, true));
			topScore = true;
			break;
		}
	}	
	if (topScore)
	{
		//remove last element of vector
		highScores.pop_back();

		//save new scores
		for (int i = 0; i < highScores.size(); i++)
		{
			std::stringstream sstm;
			sstm << "esm_place_" << (i + 1);

			CCUserDefault::sharedUserDefault()->setIntegerForKey(sstm.str().c_str(), highScores[i].getScore());
		}
		CCUserDefault::sharedUserDefault()->flush();
	}
	return highScores;
}

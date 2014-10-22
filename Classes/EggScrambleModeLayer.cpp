#include "EggScrambleModeLayer.h"
#include "Lane.h"
#include "Level.h"
#include "GameFunctions.h"
#include "EggScrambleLevelFactory.h"
#include "AcceleratingLane.h"
#include "TopScore.h"

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
		_levelManager = new LevelManager(new EggScrambleLevelFactory());

        CC_BREAK_IF(! GameLayer::init());

        bRet = true;
    } while (0);

    return bRet;
}

void EggScrambleModeLayer::initialChecks()
{
	if (_score >= _numEggsToCollect)
	{
		_score = 0; //TODO: this is a temp solution
		_numEggsToCollect++;

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

std::vector<int> EggScrambleModeLayer::checkHighScores()
{
	//all of this saving functionality should be pulled into another class
	std::vector<int> highScores;
	highScores.push_back(CCUserDefault::sharedUserDefault()->getIntegerForKey("esm_level_place_1"));
	highScores.push_back(CCUserDefault::sharedUserDefault()->getIntegerForKey("esm_level_place_2"));
	highScores.push_back(CCUserDefault::sharedUserDefault()->getIntegerForKey("esm_level_place_3"));
	highScores.push_back(CCUserDefault::sharedUserDefault()->getIntegerForKey("esm_level_place_4"));
	highScores.push_back(CCUserDefault::sharedUserDefault()->getIntegerForKey("esm_level_place_5"));

	bool topScore = false;
	for (int i = 0; i < highScores.size(); i++)
	{
		if (_score > highScores[i])
		{
			highScores.emplace(highScores.begin() + i, _score);
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
			sstm << "esm_level_place_" << (i + 1);

			CCUserDefault::sharedUserDefault()->setIntegerForKey(sstm.str().c_str(), highScores[i]);
		}
		CCUserDefault::sharedUserDefault()->flush();
	}
	return highScores;
}

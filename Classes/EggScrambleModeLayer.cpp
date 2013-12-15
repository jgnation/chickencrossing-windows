#include "EggScrambleModeLayer.h"
#include "Lane.h"
#include "Level.h"
#include "GameFunctions.h"


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

        CC_BREAK_IF(! GameLayer::init());

        bRet = true;
    } while (0);

    return bRet;
}

void EggScrambleModeLayer::initialChecks()
{
	//do nothing

	std::vector<Lane *> lanes = _level->getLanes(); //I shouldn't have to retrieve this every update
	for(std::vector<Lane *>::iterator it = lanes.begin(); it != lanes.end(); ++it) 
	{
		Lane * lane = dynamic_cast<Lane *>(*it);
		/*float currentTime = getTimeTick();
		if (lane->isTimeToSpawn(currentTime))
		{
			Vehicle * vehicle = lane->spawnVehicle();
			vehicleList.push_back(vehicle);

			vehicle->move();
			this->addChild(vehicle->getSprite());

			//set vehicle movement animation
			//delete or release at end of animation?
		}*/
		float currentTime = GameFunctions::getTimeTick();
		if (lane->isTimeToIncreaseSpeed(currentTime))
		{
			lane->increaseSpeed();
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

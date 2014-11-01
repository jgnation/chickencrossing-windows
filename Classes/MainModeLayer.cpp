#include "MainModeLayer.h"
#include "MainModeLevelFactory.h"
#include "TopScore.h"


using namespace cocos2d;

MainModeLayer::MainModeLayer(void)
{
}


MainModeLayer::~MainModeLayer(void)
{
}

CCScene* MainModeLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameLayer *layer = MainModeLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool MainModeLayer::init()
{
	//http://www.dreamincode.net/forums/topic/243971-do-while0%3B/
	//above is an explanation of do...while(0)
    bool bRet = false;
    do 
    {
		_levelNumber = 1;
		_levelManager = new LevelManager(new MainModeLevelFactory(), "mm_levels.plist");
		_nextLevelScore = calculateNextLevelScore(_levelNumber);

        CC_BREAK_IF(! GameLayer::init());

        bRet = true;
    } while (0);

    return bRet;
}
void MainModeLayer::initialChecks()
{
	if (_score >= _nextLevelScore)
	{
		this->loadNextLevel();
		_nextLevelScore = calculateNextLevelScore(_levelNumber);
	}
}

std::vector<TopScore> MainModeLayer::checkHighScores()
{
	//all of this saving functionality should be pulled into another class
	std::vector<TopScore> highScores;
	highScores.push_back(TopScore(CCUserDefault::sharedUserDefault()->getIntegerForKey("mm_place_1"), false));
	highScores.push_back(TopScore(CCUserDefault::sharedUserDefault()->getIntegerForKey("mm_place_2"), false));
	highScores.push_back(TopScore(CCUserDefault::sharedUserDefault()->getIntegerForKey("mm_place_3"), false));
	highScores.push_back(TopScore(CCUserDefault::sharedUserDefault()->getIntegerForKey("mm_place_4"), false));
	highScores.push_back(TopScore(CCUserDefault::sharedUserDefault()->getIntegerForKey("mm_place_5"), false));

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
			sstm << "mm_place_" << (i + 1);

			CCUserDefault::sharedUserDefault()->setIntegerForKey(sstm.str().c_str(), highScores[i].getScore());
		}
		CCUserDefault::sharedUserDefault()->flush();
	}
	return highScores;
}
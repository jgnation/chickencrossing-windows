#include "MenuLayer.h"
#include "GameLayer.h"
#include "MenuButtonLayer.h"
#include "LevelManager.h"
#include "Level.h"
#include "MainModeLevelFactory.h"
#include "SimpleAudioEngine.h" 

using namespace cocos2d;

CCScene* MenuLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MenuLayer *layer = MenuLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuLayer::init()
{
    bool bRet = false;
    do 
    {
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Platform80kbps.mp3", true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Platform.mp3", true);

		MenuButtonLayer * menuButtonLayer = MenuButtonLayer::create();
		this->addChild(menuButtonLayer, 5);	//z position is  on top, chicken is on 1

		LevelManager levelManager(new MainModeLevelFactory(), "mm_levels.plist");

		int levelNumber = 1;
		_level = levelManager.getLevel(levelNumber);
		_level->init();
		this->addChild(_level->getBackground()->getSprite(), 0); //added 5/24

		this->scheduleUpdate();

		bRet = true;
    } while (0);

    return bRet;
}

MenuLayer::~MenuLayer(void)
{
	delete _level;
	//TODO: delete vehicles? lanes?
}

void MenuLayer::update(float dt) 
{
	//spawn vehicles for each lane
	std::vector<Lane *> lanes = _level->getLanes(); //I shouldn't have to retrieve this every update
	for(std::vector<Lane *>::iterator it = lanes.begin(); it != lanes.end(); ++it) 
	{
		Lane * lane = dynamic_cast<Lane *>(*it);
		float currentTime = getTimeTick();
		if (lane->isTimeToSpawn(currentTime))
		{
			Vehicle * vehicle = lane->spawnVehicle();
			vehicleList.push_back(vehicle);

			vehicle->move();
			this->addChild(vehicle->getSprite(), 1);

			//set vehicle movement animation
			//delete or release at end of animation?
		}
	}

	//This loop exists to delete Vehicle objects whose sprites are finished moving across the screen.
	//I don't know if this stuff is really doing what it should be...investigate sometime.
	std::vector<Vehicle *>::iterator it = vehicleList.begin();
	while (it != vehicleList.end())
	{
		Vehicle * vehicle = dynamic_cast<Vehicle *>(*it);
		if (!vehicle->getSprite()->isVisible())
		{
			it = vehicleList.erase(it);
			//also, delete vehicle to free up memory
			//delete vehicle; <- this causes an error when I close the program for some reason.
		}
		else ++it;
	}
}

float MenuLayer::getTimeTick() 
{
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (float) millisecs;
}



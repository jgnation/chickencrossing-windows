#include "MenuLayer.h"
#include "GameLayer.h"
#include "MenuButtonLayer.h"
#include "LevelManager.h"
#include "Level.h"
#include "MainModeLevelFactory.h"
#include "SimpleAudioEngine.h"
#include "GameFunctions.h"

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

	for(std::vector<Vehicle *>::iterator it = _vehicleList.begin(); it != _vehicleList.end(); ++it) 
	{
		Vehicle * vehicle = dynamic_cast<Vehicle *>(*it);
		vehicle->release();
	}
	_vehicleList.clear(); 
}

void MenuLayer::update(float dt) 
{
	//This loop is not very elegant. This removes any vehicles from the list whose sprites have completed thier movement and were
	//removed from the parent layer.
	std::vector<Vehicle *>::iterator it = _vehicleList.begin();
	while (it != _vehicleList.end())
	{
		Vehicle * vehicle = dynamic_cast<Vehicle *>(*it);
		if (vehicle->isDoneMoving())
		{
			it = _vehicleList.erase(it);
			vehicle->release();
		}
		else ++it;
	}

	//spawn vehicles for each lane
	std::vector<Lane *> lanes = _level->getLanes(); //I shouldn't have to retrieve this every update
	for(std::vector<Lane *>::iterator it = lanes.begin(); it != lanes.end(); ++it) 
	{
		Lane * lane = dynamic_cast<Lane *>(*it);
        unsigned long long currentTime = GameFunctions::getTimeTick();
		if (lane->isTimeToSpawn(currentTime))
		{
			Vehicle * vehicle = lane->spawnVehicle();
			vehicle->retain();
			_vehicleList.push_back(vehicle);

			vehicle->move();
			this->addChild(vehicle->getSprite(), 1);
		}
	}
}



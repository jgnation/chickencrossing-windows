#include "GameLayer.h"
#include "Chicken.h"
#include "SpriteContainer.h"
#include "Car.h"
#include "Truck.h"
#include "Background.h"
#include "Bus.h"
#include "Egg.h"
#include "HUDLayer.h"
#include "LevelManager.h"
#include "Log.h"
#include "DisappearingLog.h"
#include "GameOverLayer.h"
#include "Dimensions.h"
#include "GameFunctions.h"
#include "TopScore.h"
#include "SimpleAudioEngine.h"
#include <string>

using namespace cocos2d;

//everything that gets replaced between levels will be added to the actionLayer
//when changing the level, wipe out all children from the actionLayer, change level, and then replace the children
/*
Layer hierarchy:
GameLayer
	actionLayer
		background
		vehicles
		egg
	chicken
	hudLayer
	gameoverlayer
*/

/*CCScene* GameLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameLayer *layer = GameLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}*/

/*GameLayer* GameLayer::create(GameMode* mode)
{
    GameLayer *pGOL = new GameLayer();
    if (pGOL && pGOL->init(mode)) {
        pGOL->autorelease();
        return pGOL;
    }
    CC_SAFE_DELETE(pGOL);
    return NULL;
}*/

//don't do initialization logic in the constructor, instead, do it here
bool GameLayer::init()
{
	//http://www.dreamincode.net/forums/topic/243971-do-while0%3B/
	//above is an explanation of do...while(0)
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Complete80kbps.mp3", true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Complete.mp3", true);

		this->addKeyboardSupport();

		this->setTouchEnabled(true);

		srand(time(NULL)); //seed the random number generator

		_dimensions = new Dimensions();

		_actionLayer = CCLayer::create();
		this->addChild(_actionLayer, ACTION_LAYER_POSITION);

		_chicken = new Chicken(this);

		vehicleList2 = new CCArray();

		_score = 0;
		this->addChild(_hudLayer, HUD_LAYER_POSITION);	//z position is  on top, chicken is on 1

		this->loadLevel(_levelNumber);

		_lives = 5;

		this->scheduleUpdate();

        bRet = true;
    } while (0);

    return bRet;
}

void GameLayer::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event *unused_event)
{
	if (_chicken->getSprite()->isVisible() && !_chicken->isMoving())
	{
		_chicken->setMoving(true);

		CCTouch * swipe = (CCTouch*)(touches[0]);

		CCPoint initialLocation = swipe->getPreviousLocationInView();
		initialLocation = CCDirector::sharedDirector()->convertToGL(initialLocation);
		
		//CCPoint c = swipe->getLocationInView(); //what is location vs startLocation vs prevLocation?

		CCPoint finalLocation = swipe->getStartLocationInView();
		finalLocation = CCDirector::sharedDirector()->convertToGL(finalLocation);

		//calculate slope between initial and final
		//determine the direction
		//m = (y2 - y1) / (x2 - x1)
		float slope = (finalLocation.y - initialLocation.y) / (finalLocation.x - initialLocation.x);

		if (std::abs(slope) > 1) //direction is either up or down
		{
			if (initialLocation.y > finalLocation.y) 
				_chicken->moveUp();
			else
				_chicken->moveDown();
		}
		else if (std::abs(slope) < 1) //direction is either left or right
		{
			if (initialLocation.x > finalLocation.x)
				_chicken->moveRight();
			else
				_chicken->moveLeft();
		}
		else
		{
			_chicken->setMoving(false);
			//if std::abs(slope) == 1, then the swipe was perfectly diagonal. Do nothing.
		}
	}
}

void GameLayer::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
}

void GameLayer::spriteMoveFinished3(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
	sprite->setVisible(false);
}

//this is a template method
void GameLayer::update(float dt) 
{
	this->initialChecks();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//check if a chicken riding a log is hitting the edge of the screen
	if (_chicken->isRiding())
	{
		//TODO: move this logic to chicken? _chicken->isRidingToEdgeOfScreen
		if (_chicken->getSprite()->getPositionX() < 0 || _chicken->getSprite()->getPositionX() > (winSize.width - _chicken->getSprite()->getContentSize().width))
		{
			this->killChicken();
			return;
		}

		//see if chicken is riding a log that has disappeared
		if (_chicken->getLogBeingRidden()->getSprite()->getOpacity() == 0)
		{
			this->killChicken();
			return;
		}
	}

	//getPositionY is returning a bad value after the chicken dies by running into the side of the wall
	Lane::LaneType laneType = _level->getLaneType(_dimensions->getLaneNumber(_chicken->getSprite()->getPositionY()));

	//check to see if a chicken is jumping on a log or into the water
	if (laneType == Lane::LaneType::WATER)
	{
		//bool intersectsLog = false;
		for(std::vector<Vehicle *>::iterator it = vehicleList.begin(); it != vehicleList.end(); ++it) 
		{
			Vehicle * vehicle = dynamic_cast<Vehicle *>(*it);

			//I shouldn't have to check the base-class type.  I will revisit this issue later.
			Log* log = dynamic_cast<Log*>(vehicle); //this will work for DisappearingLogs as well
			if(log != 0)
			{
				if (_chicken->intersectsSprite(log) && !_chicken->isMoving())
				{
					if (!_chicken->isRiding())
					{
						_chicken->ride(log);
					}
				}
			}
		}
		//keep in mind that with the way chicken is currently built....it is not "riding" when it is "moving"...
		//...even if it is on a log.  It can be riding, moving, and then still be on the log and be riding again
		if (!_chicken->isMoving() && !_chicken->isRiding())
		{
			//chicken is in the water
			this->killChicken();
		}
	}

	//check to see if a chicken has been hit by a vehicle
	//If I had a CCArray of CCObjects, I could use CCARRAY_FOREACH here
	if (laneType == Lane::LaneType::ROAD)
	{
		for(std::vector<Vehicle *>::iterator it = vehicleList.begin(); it != vehicleList.end(); ++it) 
		{
			Vehicle * vehicle = dynamic_cast<Vehicle *>(*it);

			if (_chicken->intersectsSprite(vehicle))
			{
				this->killChicken();
			}			
		}
	}

	//check to see if kitchen has collected an egg
	if (_chicken->intersectsSprite(_egg))
	{
		//move the egg
		CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
		float x = GameFunctions::randomValueBetween((float)0, (windowSize.width - _egg->getSprite()->getContentSize().width));
		float y = _dimensions->getLanePixelValue(_level->getRandomValidLaneNumber());
		_egg->setPosition(x, y);

		//increment the score
		_score++;
		_hudLayer->setScore(_score);
	}

	//spawn vehicles for each lane
	std::vector<Lane *> lanes = _level->getLanes(); //I shouldn't have to retrieve this every update
	for(std::vector<Lane *>::iterator it = lanes.begin(); it != lanes.end(); ++it) 
	{
		Lane * lane = dynamic_cast<Lane *>(*it);
		float currentTime = GameFunctions::getTimeTick();
		if (lane->isTimeToSpawn(currentTime))
		{
			Vehicle * vehicle = lane->spawnVehicle();
			vehicleList.push_back(vehicle);

			vehicle->move();
			_actionLayer->addChild(vehicle->getSprite(), VEHICLES_POSITION);

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

//this logic should be in the chicken class
void GameLayer::killChicken()
{
	//decrement the number of lives remaining
	_lives--;
	_hudLayer->setLives(_lives);

	_chicken->die();

	if (_lives <= 0)
	{
		this->gameOver();
	}
}


void GameLayer::gameOver()
{
	_chicken->getSprite()->setVisible(false);

	std::vector<TopScore> highScores = this->checkHighScores();

	//display GameOver with a next button
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	GameOverLayer* gameOverLayer = new GameOverLayer();
	gameOverLayer->init(highScores);
	this->addChild(gameOverLayer, GAME_OVER_LAYER_POSITION);
}

void GameLayer::resetChicken()
{
	_chicken->die();
}

void GameLayer::loadLevel(int levelNumber)
{
	_actionLayer->removeAllChildren(); //remove all with cleanup?

	this->resetChicken();

	_numEggsToCollect = levelNumber;
	_hudLayer->setLevel(levelNumber);
	_hudLayer->setScore(_score);

	_level = _levelManager->getLevel(levelNumber);
	_level->init();
	_actionLayer->addChild(_level->getBackground()->getSprite(), BACKGROUND_POSITION);

	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	_egg = new Egg();
	float x = GameFunctions::randomValueBetween((float)0, (windowSize.width - _egg->getSprite()->getContentSize().width));
	float y = _dimensions->getLanePixelValue(_level->getRandomValidLaneNumber());
	_egg->setPosition(x, y);
	_actionLayer->addChild(_egg->getSprite(), EGG_POSITION);

	//this fixes the bug where at the beginning of the second level, if the chicken moved
	//up quickly, it would randomly die.  I think this might also be creating memory leaks.
	vehicleList.clear(); 
	//random_shuffle(vehicleList.begin, vehicleList.end);
}

void GameLayer::loadNextLevel()
{
	//I should probably call a method here to clean up dynamically allocated objects, and add a 'you win!' capation
	this->loadLevel(++_levelNumber);
}

void GameLayer::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (_chicken->getSprite()->isVisible())
	{
		if (!_chicken->isMoving())
		{
			_chicken->setMoving(true);

			if (keyCode == EventKeyboard::KeyCode::KEY_W)
			{
				_chicken->moveUp();
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_S)
			{
				_chicken->moveDown();
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_A)
			{
				_chicken->moveLeft();
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_D)
			{
				_chicken->moveRight();
			}
		}
	}
}

void GameLayer::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    //do nothing
}


void GameLayer::addKeyboardSupport()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameLayer::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameLayer::keyReleased, this);

	EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

int GameLayer::calculateNextLevelScore(int levelNumber)
{
	if (levelNumber == 0)
	{
		return 0;
	}
	return levelNumber + calculateNextLevelScore(levelNumber - 1);
}


#include "GameLayer.h"
#include "Chicken.h"
#include "SpriteContainer.h"
#include "Car.h"
#include "Truck.h"
#include "Background.h"
#include "Bus.h"
#include "Egg.h"
#include "HUDLayer.h"
#include "PauseLayer.h"
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

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Complete.mp3", true);
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(.9);

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
		_isGameOver = false;
        _isPaused = false;
		_pauseLayer = new PauseLayer();
		_pauseLayer->init();
		this->addChild(_pauseLayer, PAUSE_LAYER_POSITION);

		this->scheduleUpdate();

        bRet = true;
    } while (0);

    return bRet;
}

void GameLayer::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event *unused_event)
{
	if (!_isPaused && _chicken->getSprite()->isVisible() && !_chicken->isMoving())
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

void GameLayer::update(float dt)
{
    if (!_isPaused)
    {
        doUpdate(dt);
    }
}

//this is a template method
void GameLayer::doUpdate(float dt)
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

	this->initialChecks();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//check if a chicken riding a log is hitting the edge of the screen
	if (_chicken->isRiding())
	{
		//TODO: move this logic to chicken? _chicken->isRidingToEdgeOfScreen
		if (_chicken->getSprite()->getPositionX() < 0 || _chicken->getSprite()->getPositionX() > (winSize.width - _chicken->getSprite()->getBoundingBox().size.width))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("253173__suntemple__retro-falling-down-sfx.wav");
			this->killChicken();
			return;
		}

		//see if chicken is riding a log that has disappeared
		if (_chicken->getLogBeingRidden()->getSprite()->getOpacity() == 0)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("212143__qubodup__splash-by-blaukreuz.wav"); 
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
		for(std::vector<Vehicle *>::iterator it = _vehicleList.begin(); it != _vehicleList.end(); ++it) 
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
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("212143__qubodup__splash-by-blaukreuz.wav");
			this->killChicken();
		}
	}

	//check to see if a chicken has been hit by a vehicle
	//If I had a CCArray of CCObjects, I could use CCARRAY_FOREACH here
	if (laneType == Lane::LaneType::ROAD)
	{
		for(std::vector<Vehicle *>::iterator it = _vehicleList.begin(); it != _vehicleList.end(); ++it) 
		{
			Vehicle * vehicle = dynamic_cast<Vehicle *>(*it);

			if (_chicken->intersectsSprite(vehicle))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("253173__suntemple__retro-falling-down-sfx.wav"); 
				this->killChicken();
			}			
		}
	}

	//check to see if kitchen has collected an egg
	if (_chicken->intersectsSprite(_egg))
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("253177__suntemple__retro-accomplished-sfx.wav");

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
			vehicle->retain();
			_vehicleList.push_back(vehicle);

			vehicle->move();
			_actionLayer->addChild(vehicle->getSprite(), VEHICLES_POSITION);

			//set vehicle movement animation
			//delete or release at end of animation?
		}
	}
}

//this logic should be in the chicken class
void GameLayer::killChicken()
{
	//decrement the number of lives remaining
	_lives--;
	_hudLayer->setLives(_lives);

	if (_lives <= 0)
	{
		_chicken->die(false);
		this->gameOver();
	}
	else
	{
		_chicken->die(true);
	}
}


void GameLayer::gameOver()
{
	_isGameOver = true;
	_chicken->getSprite()->setVisible(false);

	std::vector<TopScore> highScores = this->checkHighScores();
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);

	//display GameOver with a next button
	GameOverLayer* gameOverLayer = new GameOverLayer();
	gameOverLayer->init(highScores);
	this->addChild(gameOverLayer, GAME_OVER_LAYER_POSITION);
}

void GameLayer::resetChicken()
{
	_chicken->reset();
}

void GameLayer::loadLevel(int levelNumber)
{
	_actionLayer->removeAllChildrenWithCleanup(true);

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
	//up quickly, it would randomly die.
	for(std::vector<Vehicle *>::iterator it = _vehicleList.begin(); it != _vehicleList.end(); ++it) 
	{
		Vehicle * vehicle = dynamic_cast<Vehicle *>(*it);
		//vehicle->finishMovement(); //this isn't necessary because of the _actionLayer->removeAllChildrenWithCleanup(true) call
		vehicle->release();
	}
	_vehicleList.clear(); 
}

void GameLayer::loadNextLevel()
{
	//I should probably call a method here to clean up dynamically allocated objects, and add a 'you win!' capation
	this->loadLevel(++_levelNumber);
}

void GameLayer::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (!_isPaused && _chicken->getSprite()->isVisible() && !_chicken->isMoving())
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

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	//EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

int GameLayer::calculateNextLevelScore(int levelNumber)
{
	if (levelNumber == 0)
	{
		return 0;
	}
	return levelNumber + calculateNextLevelScore(levelNumber - 1);
}

void GameLayer::pauseGame()
{
	if (!_isGameOver)
	{
        _isPaused = true;
        Vector<Node*> children = _actionLayer->getChildren();
        for (auto child : children)
        {
            child->pauseSchedulerAndActions();
        }
		_pauseLayer->pause();
	}
}

void GameLayer::resumeGame()
{
    Vector<Node*> children = _actionLayer->getChildren();
    for (auto child : children)
    {
        child->resumeSchedulerAndActions();
    }
    _isPaused = false;
    //Director::getInstance()->startAnimation();
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


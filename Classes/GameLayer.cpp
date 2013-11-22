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
#include <string>

using namespace cocos2d;

CCScene* GameLayer::scene()
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
}

//don't do initialization logic in the constructor, instead, do it here
bool GameLayer::init()
{
	//http://www.dreamincode.net/forums/topic/243971-do-while0%3B/
	//above is an explanation of do...while(0)
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
		this->setTouchEnabled(true);

		srand(time(NULL)); //seed the random number generator

		vehicleList2 = new CCArray();

		_hudLayer = new HudLayer();
		_hudLayer->init();
		this->addChild(_hudLayer, 2);	//z position is  on top, chicken is on 1

		_levelManager = new LevelManager();
		_levelNumber = 1;
		this->loadLevel(_levelNumber);

		this->scheduleUpdate();

        bRet = true;
    } while (0);

    return bRet;
}

void GameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	if (!_chicken->isMoving())
	{
		_chicken->setMoving(true);
		//Get location of touch
		//compare location to current position of chicken
		//move chicken in direction of touch

		CCTouch* touch = (CCTouch*)( touches->anyObject() );
		CCPoint touchLocation = touch->locationInView();
		touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

		//CCPoint currentLocation = _chicken->getPoint();
		CCPoint currentLocation = _chicken->getSprite()->getPosition();

		//the greatest difference in coordinates is the direction in which we will move
		int xDiff = touchLocation.x - currentLocation.x;
		int yDiff = touchLocation.y - currentLocation.y;

		int xDiffAbs = this->getAbsoluteValue(xDiff);
		int yDiffAbs = this->getAbsoluteValue(yDiff);

		//TODO take into account where coordinates is equal
		if (yDiffAbs > xDiffAbs && yDiff > 0)
			_chicken->moveUp();
		else if (yDiffAbs > xDiffAbs && yDiff < 0)
			_chicken->moveDown();
		else if (xDiffAbs > yDiffAbs && xDiff > 0)
			_chicken->moveRight();
		else if (xDiffAbs > yDiffAbs && xDiff < 0)
			_chicken->moveLeft();
	}
}

//I implemented my own just because I am not sure about cross-platform compatibility of c libraries (cmath)
int GameLayer::getAbsoluteValue(int num)
{
	if (num < 0)
		return num * (-1);
	else
		return num;
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

float GameLayer::randomValueBetween(float low , float high) 
{
	return rand() % (int)high + (int)low;
}

float GameLayer::getLanePixelPosition(int laneNumber)
{
	//the lane at the bottom of the screen is lane 1
	int validLanes[10] = {3, 4, 5, 6, 7, 9, 10, 11, 12, 13};
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float lanePosition = (windowSize.height / 16) * validLanes[laneNumber];
	float laneWidth = windowSize.height / 16;
	return lanePosition - (laneWidth / 2); //return the center of the lane
}

int GameLayer::getLaneNumber(float pixelPosition)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float laneWidth = windowSize.height / 16;
	float lane = pixelPosition / laneWidth; //this will return the lane in indexes from 0
	lane++; //add 1 to get the lane in natural index (from 1)
	int laneNumber = static_cast <int> (std::floor(lane)); //is this fragile?
	return laneNumber;
}

int GameLayer::getRandomLaneNumber()
{
	int validLanes[10] = {3, 4, 5, 6, 7, 9, 10, 11, 12, 13};
	return (int)randomValueBetween(0.0, 9.0);
}
 
float GameLayer::getTimeTick() 
{
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (float) millisecs;
}

void GameLayer::update(float dt) 
{
	if (_score >= _numEggsToCollect)
	{
		this->resetChicken();
		this->loadNextLevel();
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//check if a chicken riding a log is hitting the edge of the screen
	if (_chicken->isRiding())
	{
		if (_chicken->getSprite()->getPositionX() < 0 || _chicken->getSprite()->getPositionX() > winSize.width)
		{
			this->killChicken();
		}
	}

	//getPositionY is returning a bad value after the chicken dies by running into the side of the wall
	Level::LaneType laneType = _level->getLaneType(this->getLaneNumber(_chicken->getSprite()->getPositionY()));

	//check to see if a chicken is jumping on a log or into the water
	if (laneType == Level::LaneType::WATER)
	{
		bool intersectsLog = false;
		for(std::vector<Vehicle *>::iterator it = vehicleList.begin(); it != vehicleList.end(); ++it) 
		{
			Vehicle * vehicle = dynamic_cast<Vehicle *>(*it);

			//I shouldn't have to check the base-class type.  I will revisit this issue later.
			Log* log = dynamic_cast<Log*>(vehicle);
			if(log != 0)
			{
				if (_chicken->intersectsSprite(log) && !_chicken->isMoving())
				{
					_chicken->ride(log);

					intersectsLog = true;
				}
			}
		}
		if (!intersectsLog && !_chicken->isMoving()) //when debugging, this value might be incorrect due to the log still moving
		{
			this->killChicken();
		}
	}

	//check to see if a chicken has been hit by a vehicle
	//If I had a CCArray of CCObjects, I could use CCARRAY_FOREACH here
	if (laneType == Level::LaneType::ROAD)
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
		float a = this->randomValueBetween(0, windowSize.width);
		float b = this->getLanePixelPosition(this->getRandomLaneNumber());
		_egg->setPosition(a, b);

		//increment the score
		_score++;
		_hudLayer->setScore(_score);
	}

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
			this->addChild(vehicle->getSprite());

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
}

void GameLayer::resetChicken()
{
	_chicken->die();
}

void GameLayer::loadLevel(int levelNumber)
{
	_numEggsToCollect = levelNumber;
	_score = 0;									//I will probably not want to reset this in the future
	_hudLayer->setScore(_score);
	_lives = 5;
	_hudLayer->setLives(_lives);
	_level = _levelManager->getLevel(levelNumber);
	this->addChild(_level->getBackground()->getSprite());

	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float a = this->randomValueBetween(0, windowSize.width);
	float b = this->getLanePixelPosition(this->getRandomLaneNumber());
	_egg = new Egg(a, b);
	this->addChild(_egg->getSprite());

	_chicken = new Chicken(this);			
	//random_shuffle(vehicleList.begin, vehicleList.end);
}

void GameLayer::loadNextLevel()
{
	//I should probably call a method here to clean up dynamically allocated objects, and add a 'you win!' capation
	this->loadLevel(++_levelNumber);
}
#include "GameLayer.h"
#include "Chicken.h"
#include "SpriteContainer.h"
#include "Car.h"
#include "Truck.h"
#include "Background.h"
#include "Bus.h"
#include "Egg.h"
#include "HUDLayer.h"
#include "Level.h"
#include "Level1.h"
#include "Log.h"
#include "Level2.h"

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

		_score = 0;
		_lives = 5;

		_level = new Level2();
		this->addChild(_level->getBackground()->getSprite());

		//_background = new Background("background.png");
		//this->addChild(_background->getSprite());

		_hudLayer = new HudLayer();
		_hudLayer->init();
		this->addChild(_hudLayer);

		CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
		float a = this->randomValueBetween(0, windowSize.width);
		float b = this->getLanePixelPosition(this->getRandomLaneNumber());
		_egg = new Egg(a, b);
		this->addChild(_egg->getSprite());

		_chicken = new Chicken(this);			

		//precreate vehicles rather than doing it dynamically
		#define K_NUM_VEHICLES 25
		for(int i = 0; i < K_NUM_VEHICLES; ++i) 
		{
			//TODO: vehicle creation should be randomized
			if (i % 2 == 0 && i % 4 != 0)
			{
				Truck * truck = new Truck();
				vehicleList.push_back(truck);
			}
			else
			{
				if (i %  3 == 0)
				{
					Car * car = new Car();
					vehicleList.push_back(car);
				}
				else
				{
					if (i % 4 == 0)
					{
						Bus * bus = new Bus();
						vehicleList.push_back(bus);
					}
					else
					{
						Log * log = new Log();
						vehicleList.push_back(log);						
					}
				}
			}
		}
		_nextVehicle = 0;
		//random_shuffle(vehicleList.begin, vehicleList.end);

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

void GameLayer::startMovement(Vehicle * vehicle)
{
	CCFiniteTimeAction* actionMove = CCMoveTo::create(vehicle->getSpeed(), vehicle->getDestination());
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::spriteMoveFinished));
	vehicle->getSprite()->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void GameLayer::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
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
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//check if a chicken riding a log is hitting the edge of the screen
	if (_chicken->isRiding())
	{
		if (_chicken->getSprite()->getPositionX() < 0 || _chicken->getSprite()->getPositionX() > winSize.width)
		{
			this->killChicken();
		}
	}

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
					//initiate the riding animation
					int logSpeed = log->getSpeed();
					CCPoint destination = log->getDestination();

					float distance = ccpDistance(_chicken->getSprite()->getPosition(), destination);
					float duration = distance / logSpeed;

					//should this be done in the chicken class?
					CCFiniteTimeAction* actionMove = CCMoveTo::create(duration, destination);
					CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::spriteMoveFinished));
					_chicken->getSprite()->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
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

	//next section is for spawning vehicles
	float curTimeMillis = getTimeTick();
	if (curTimeMillis > _nextVehicleSpawn) //TODO: I haven't initialized _nextVehicleSpawn anywhere yet
	{ 
		//the values that I am inputting depend on the new version of randomValueBetween that I modified
		float randMillisecs = randomValueBetween(5, 15) * 100;
		_nextVehicleSpawn = randMillisecs + curTimeMillis;

		//int randomLane = this->getRandomLaneNumber();
		//float randY = this->getLanePixelPosition(randomLane);
		float randDuration = this->randomValueBetween(2.0, 10.0);

		Vehicle *  vehicle = vehicleList[_nextVehicle];
		_nextVehicle++;
 
		if (_nextVehicle >= vehicleList.size())
			_nextVehicle = 0;	

		Log* log = dynamic_cast<Log*>(vehicle);
		//this stuff works for Level2!
		int randomLane = 0;
		if(log != 0)
		{
			//it's a log
			randomLane = this->getRandomLaneNumber();
			while (randomLane < 5)
			{
				randomLane = this->getRandomLaneNumber();
			}
		}
		else
		{
			//it's not a log
			randomLane = this->getRandomLaneNumber();
			while (randomLane > 4)
			{
				randomLane = this->getRandomLaneNumber();
			}
		}
		float randY = this->getLanePixelPosition(randomLane);

		CCFiniteTimeAction* actionMove;
		if (randomLane % 2 == 0)
		{
			vehicle->getSprite()->setPosition(ccp(winSize.width, randY));
			CCPoint destination = ccp(-120, randY); //-120 so the sprite goes completely off screen.  This should be scaled
			vehicle->setDestination(destination);
			int speed = vehicle->getSpeed();
			float distance = ccpDistance(ccp(winSize.width, randY), destination);
			float duration = distance / speed;
			actionMove = CCMoveTo::create(duration, destination); 
			vehicle->getSprite()->setFlipX(false);
		}
		else
		{
			vehicle->getSprite()->setPosition(ccp(0, randY));
			CCPoint destination = ccp(winSize.width + 120, randY);
			int speed = vehicle->getSpeed();
			float distance = ccpDistance(ccp(0, randY), destination);
			float duration = distance / speed;
			actionMove = CCMoveTo::create(duration, destination); //+120 so the sprite goes completely off screen.  This should be scaled
			vehicle->setDestination(destination);
			vehicle->setMovementAction(actionMove);
			//note: 120 is the width of the bus.  This fixes the issue where the chicken dies if the egg is at the left of the screen.
			if (!vehicle->getSprite()->isFlipX()) vehicle->getSprite()->setFlipX(true);
		}

		CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::spriteMoveFinished));
		vehicle->getSprite()->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
		this->addChild(vehicle->getSprite());
	}
}

void GameLayer::resetFlag()
{
	//doing this directly in update did not work for some reason.
	//now I call this->resetFlag() and it works.  Huh.
	_chicken->setMoving(false);
}

void GameLayer::setInvisible(CCNode * node) 
{
	node->setVisible(false);
}

//this logic should be in the chicken class
void GameLayer::killChicken()
{
	//decrement the number of lives remaining
	_lives--;
	_hudLayer->setLives(_lives);

	_chicken->die();

	this->resetFlag();
}
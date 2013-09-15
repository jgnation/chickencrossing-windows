#include "GameScene.h"
#include "Chicken.h"
#include "SpriteContainer.h"
#include "Car.h"
#include "Truck.h"
#include "Background.h"

using namespace cocos2d;

bool GameScene::_isMoving = false;

CCScene* GameScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameScene *layer = GameScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

//don't do initialization logic in the constructor, instead, do it here
bool GameScene::init()
{
	//http://www.dreamincode.net/forums/topic/243971-do-while0%3B/
	//above is an explanation of do...while(0)
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
		this->setTouchEnabled(true);

		_background = new Background();
		this->addChild(_background->getSprite());

		_chicken = new Chicken(this);			

		//precreate vehicles rather than doing it dynamically
		#define K_NUM_VEHICLES 15
		for(int i = 0; i < K_NUM_VEHICLES; ++i) 
		{
			//TODO: vehicle creation should be randomized
			if (i % 2 == 0)
			{
				Truck * truck = new Truck();
				vehicleList.push_back(truck);
			}
			else
			{
				Car * car = new Car();
				vehicleList.push_back(car);
			}
		}
		_nextVehicle = 0;
		//random_shuffle(vehicleList.begin, vehicleList.end);

		this->scheduleUpdate();

        bRet = true;
    } while (0);

    return bRet;
}

void GameScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	if (GameScene::_isMoving == false)
	{
		GameScene::_isMoving = true;
		//Get location of touch
		//compare location to current position of chicken
		//move chicken in direction of touch

		CCTouch* touch = (CCTouch*)( touches->anyObject() );
		CCPoint touchLocation = touch->locationInView();
		touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

		CCPoint currentLocation = _chicken->getPoint();
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

		CCFiniteTimeAction* actionMove = CCMoveTo::create(1, _chicken->getPoint());
		CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameScene::spriteMoveFinished2));
		_chicken->getSprite()->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
}

//I implemented my own just because I am not sure about cross-platform compatibility of c libraries (cmath)
int GameScene::getAbsoluteValue(int num)
{
	if (num < 0)
		return num * (-1);
	else
		return num;
}

void GameScene::startMovement(Vehicle * vehicle)
{
	CCFiniteTimeAction* actionMove = CCMoveTo::create(vehicle->getSpeed(), vehicle->getDestination());
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameScene::spriteMoveFinished));
	vehicle->getSprite()->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void GameScene::spriteMoveFinished2(CCNode* sender)
{
	//CCSprite *sprite = (CCSprite *)sender;
	//this->removeChild(sprite, true);
	GameScene::_isMoving = false;
}

void GameScene::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
}

float GameScene::randomValueBetween(float low , float high) 
{
	return rand() % (int)high + (int)low;
}

float GameScene::getRandomLanePosition()
{
	//the lane at the bottom of the screen is lane 1
	int validLanes[10] = {3, 4, 5, 6, 7, 9, 10, 11, 12, 13};
	int randomIndex = (int)randomValueBetween(0.0, 9.0);
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	return (windowSize.height / 16) * validLanes[randomIndex];
}
 
float GameScene::getTimeTick() 
{
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (float) millisecs;
}

void GameScene::update(float dt) 
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//check for overlap of chicken sprite and vehicle sprites
	//If I had a CCArray of CCObjects, I could use CCARRAY_FOREACH here
	for(std::vector<Vehicle *>::iterator it = vehicleList.begin(); it != vehicleList.end(); ++it) 
	{
		Vehicle * vehicle = dynamic_cast<Vehicle *>(*it);

		if (_chicken->intersectsSprite(vehicle))
		{
			//reset position of chicken
			this->removeChild(_chicken->getSprite(), true);
			_chicken = new Chicken(this);
			this->resetFlag();
		}
	}

	//next section is for spawning vehicles
	float curTimeMillis = getTimeTick();
	if (curTimeMillis > _nextVehicleSpawn) //TODO: I haven't initialized _nextVehicleSpawn anywhere yet
	{ 
		//the values that I am inputting depend on the new version of randomValueBetween that I modified
		float randMillisecs = randomValueBetween(5, 15) * 100;
		_nextVehicleSpawn = randMillisecs + curTimeMillis;
 
		CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
		float laneWidth = windowSize.height / 16;

		float randY = this->getRandomLanePosition() - (laneWidth / 2);
		float randDuration = randomValueBetween(2.0, 10.0);

		Vehicle *  vehicle = vehicleList[_nextVehicle];
		_nextVehicle++;
 
		if (_nextVehicle >= vehicleList.size())
			_nextVehicle = 0;		
		
		vehicle->getSprite()->setPosition(ccp(winSize.width - 100, randY));
		this->addChild(vehicle->getSprite());

		CCFiniteTimeAction* actionMove = CCMoveTo::create(3, ccp(0, randY));
		CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameScene::spriteMoveFinished));
		vehicle->getSprite()->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
}

void GameScene::resetFlag()
{
	//doing this directly in update did not work for some reason.
	//not I call this->resetFlag() and it works.  Huh.
	GameScene::_isMoving = false;
}

void GameScene::setInvisible(CCNode * node) 
{
	node->setVisible(false);
}
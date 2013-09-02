#include "GameScene.h"
#include "Chicken.h"
#include "SpriteContainer.h"
#include "Car.h"

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

		//http://www.cocos2d-iphone.org/forums/topic/changing-the-aspect-fit-of-an-image-on-a-sprite-or-a-layer/
		//set up background image and scale it appropriately
		_backgroundSprite = CCSprite::create("background.png");
		_backgroundSprite->setAnchorPoint(ccp(0, 0));
		_backgroundSprite->setPosition(ccp(0, 0));
		CCSize winSize = CCDirector::sharedDirector()->getWinSize(); //640 x 480
		_backgroundSprite->setScaleX(winSize.width / _backgroundSprite->getContentSize().width);   //640 / 720
		_backgroundSprite->setScaleY(winSize.height / _backgroundSprite->getContentSize().height); //480 / 960
		this->addChild(_backgroundSprite);

		_chicken = new Chicken(this);		

		//SpriteContainer * car = new Car();
		//The above line also works.  I'm not sure what the difference is...
		Car * car = new Car();
		this->addChild(car->getSprite());
		this->startMovement(car);

		//precreate vehicles rather than doing it dynamically
		#define KNUMASTEROIDS 15
		_vehicles = new CCArray(); 
		for(int i = 0; i < KNUMASTEROIDS; ++i) 
		{
			//CCSprite *v = CCSprite::spriteWithSpriteFrameName("red_car.png");
			CCSprite * v = CCSprite::create("red_car.png", CCRectMake(0, 0, 82, 25));
			v->setVisible(false);
			//_batchNode->addChild(asteroid);	//what is batch node?
			_vehicles->addObject(v);
		}
		_nextVehicle = 0;

		this->scheduleUpdate();
		//this->setto

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

float GameScene::randomValueBetween( float low , float high ) 
{
    //return (((float) rand() / 0xFFFFFFFFu) * (high - low)) + low;
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
	CCSprite * chickenSprite = _chicken->getSprite();
	CCRect chickenRect = CCRectMake(
			chickenSprite->getPosition().x - (chickenSprite->getContentSize().width / 2),
			chickenSprite->getPosition().y - (chickenSprite->getContentSize().height / 2),
			chickenSprite->getContentSize().width,
			chickenSprite->getContentSize().height);

	CCObject* it = NULL;
	CCARRAY_FOREACH(_vehicles, it)
	{
		CCSprite *vehicle = dynamic_cast<CCSprite*>(it);
		CCRect vehicleRect = CCRectMake(
			vehicle->getPosition().x - (vehicle->getContentSize().width / 2),
			vehicle->getPosition().y - (vehicle->getContentSize().height / 2),
			vehicle->getContentSize().width,
			vehicle->getContentSize().height);

		if (vehicleRect.intersectsRect(chickenRect))
		{
			//reset position of chicken
			this->removeChild(chickenSprite, true);
			_chicken = new Chicken(this);
			this->resetFlag();
		}
	}

	//next section is for spawning vehicles
	float curTimeMillis = getTimeTick();
	if (curTimeMillis > _nextVehicleSpawn) 
	{ 
		//the values that I am inputting depend on the new version of randomValueBetween that I modified
		float randMillisecs = randomValueBetween(5,15) * 100;
		_nextVehicleSpawn = randMillisecs + curTimeMillis;
 
		float randY = this->getRandomLanePosition() - 12; //TODO: this 12 needs to be a scaled value
		//float randY = randomValueBetween(0.0,winSize.height);
		float randDuration = randomValueBetween(2.0,10.0);

		//CCSprite *asteroid = _vehicles->getObjectAtIndex(_nextVehicle);
		CCSprite *vehicle = (CCSprite *) _vehicles->objectAtIndex(_nextVehicle);
		_nextVehicle++;
 
		if (_nextVehicle >= _vehicles->count())
			_nextVehicle = 0;
 
		//vehicle->stopAllActions();
		vehicle->setPosition( ccp(winSize.width - 100, randY));
		vehicle->setVisible(true) ;
		this->addChild(vehicle);	//this wouldn't be necessary if I added it to batchnode
		/*vehicle->runAction ( CCSequence::actions (
			CCMoveBy::actionWithDuration(randDuration,ccp(-winSize.width-vehicle->getContentSize().width,0)) , 
			CCCallFuncN::actionWithTarget(this,callfuncN_selector(GameScene::setInvisible)) ,
			NULL // DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)
			) ) ; */
		CCFiniteTimeAction* actionMove = CCMoveTo::create(3, ccp(0, randY));
		CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameScene::spriteMoveFinished));
		vehicle->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
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
	node->setVisible(false) ;
}




#include "Lane.h"
#include "Car.h"

using namespace cocos2d;

Lane::Lane(CCDictionary * lane, int laneNumber)
{
	_laneNumber = laneNumber;
	_nextSpawnTime = 0;

	CCString * laneTypeCCString = (CCString *) lane->objectForKey("Type");
	_type = laneTypeCCString->getCString();

	_interval = lane->valueForKey("Interval")->floatValue();

	_speed = lane->valueForKey("Speed")->intValue();
}

bool Lane::isTimeToSpawn(float currentTime)
{
	if (_type == "WATER" || _type == "ROAD")
	{
		if (currentTime > _nextSpawnTime) 
		{ 
			_nextSpawnTime = _interval + currentTime;
			return true;
		}
	}
	return false;
}

//check list of acceptable cars for this lane.  randomly pick one, create it, return it
Vehicle * Lane::spawnVehicle()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	Car * car = new Car();
	float y = this->getLanePixelPosition(_laneNumber);
	_y = y;

	car->getSprite()->setPosition(ccp(windowSize.width, y));
	CCPoint destination = ccp(-120, y); //-120 so the sprite goes completely off screen.  This should be scaled
	car->setDestination(destination);

	car->setSpeed(_speed);

	return car; //TODO
}

float Lane::getLanePixelPosition(int laneNumber)
{
	//the lane at the bottom of the screen is lane 1
	int validLanes[10] = {3, 4, 5, 6, 7, 9, 10, 11, 12, 13};
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float lanePosition = (windowSize.height / 16) * validLanes[laneNumber];
	float laneWidth = windowSize.height / 16;
	return lanePosition - (laneWidth / 2); //return the center of the lane
}

float Lane::getY()
{
	return _y;
}

int Lane::getSpeed()
{
	return _speed;
}
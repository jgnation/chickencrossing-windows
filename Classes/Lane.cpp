#include "Lane.h"
#include "Car.h"
#include "Bus.h"
#include "Truck.h"
#include "Log.h"

using namespace cocos2d;

Lane::Lane(CCDictionary * lane, int laneNumber)
{
	_laneNumber = laneNumber;
	_nextSpawnTime = 0;

	CCString * laneTypeCCString = (CCString *) lane->objectForKey("Type");
	_type = laneTypeCCString->getCString();

	_interval = lane->valueForKey("Interval")->floatValue();

	_speed = lane->valueForKey("Speed")->intValue();

	CCArray * vehicles = (CCArray *) lane->objectForKey("Vehicles");
	CCObject *it;
	CCARRAY_FOREACH(vehicles, it)
	{
		CCString * vehicle = dynamic_cast<CCString *>(it);
		_vehicles.push_back(vehicle->getCString());
	}
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

	Vehicle * vehicle = this->getRandomVehicle();
	float y = this->getLanePixelPosition(_laneNumber);

	if (_laneNumber % 2 == 0)
	{
		vehicle->getSprite()->setPosition(ccp(windowSize.width, y));
		CCPoint destination = ccp(-120, y); //-120 so the sprite goes completely off screen.  This should be scaled
		vehicle->setDestination(destination);
		vehicle->getSprite()->setFlipX(false);
	}
	else
	{
		vehicle->getSprite()->setPosition(ccp(0, y));
		CCPoint destination = ccp(windowSize.width + 120, y);
		vehicle->setDestination(destination);
		if (!vehicle->getSprite()->isFlipX()) vehicle->getSprite()->setFlipX(true);
	}

	vehicle->setSpeed(_speed);

	return vehicle;
}

Vehicle * Lane::getRandomVehicle()
{
	int randomIndex = this->randomValueBetween(0, _vehicles.size());
	std::string vehicle = _vehicles.at(randomIndex);

	if (vehicle == "Car")
	{
		return new Car();
	}
	else if (vehicle == "Bus")
	{
		return new Bus();
	}
	else if (vehicle == "Truck")
	{
		return new Truck();
	}
	else if (vehicle == "Log")
	{
		return new Log();
	}
	else
	{
		return NULL; //this is an error, should throw an exception
	}
}

int Lane::randomValueBetween(int low , int high) 
{
	return rand() % (int)high + (int)low;
}

float Lane::getLanePixelPosition(int laneNumber)
{
	//the lane at the bottom of the screen is lane 1
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float lanePosition = (windowSize.height / 16) * laneNumber;
	float laneWidth = windowSize.height / 16;
	return lanePosition - (laneWidth / 2); //return the center of the lane
}

int Lane::getSpeed()
{
	return _speed;
}
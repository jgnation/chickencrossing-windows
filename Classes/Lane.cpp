#include "Lane.h"
#include "Car.h"
#include "Bus.h"
#include "Truck.h"
#include "Log.h"
#include "DisappearingLog.h"

using namespace cocos2d;

Lane::Lane(CCDictionary * lane, int laneNumber)
{
	_vehicleFactory = new VehicleFactory();
	_dimensions = new Dimensions();

	_laneNumber = laneNumber;
	_nextSpawnTime = 0;
	_increaseSpeedInterval = 4000.0;	//pull this into config
	_nextIncreaseSpeedTime = 0;

	CCString * laneTypeCCString = (CCString *) lane->objectForKey("Type");
	_type = laneTypeCCString->getCString();

	_interval = lane->valueForKey("Interval")->floatValue();
	if (_interval == 0)
	{
		//get random interval
		_interval = this->randomValueBetween(2000, 3000);
	}

	_speed = lane->valueForKey("Speed")->intValue();
	if (_speed == 0)
	{
		//get random speed
		_speed = this->randomValueBetween(80, 150);
	}

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

bool Lane::isTimeToIncreaseSpeed(float currentTime)
{
	if (currentTime > _nextIncreaseSpeedTime)
	{
		_nextIncreaseSpeedTime = _increaseSpeedInterval + currentTime;
		return true;
	}
	return false;
}

//check list of acceptable cars for this lane.  randomly pick one, create it, return it
Vehicle * Lane::spawnVehicle()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	Vehicle * vehicle = this->getRandomVehicle();
	float y = _dimensions->getCenterOfLanePixelValue(_laneNumber);

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

	return _vehicleFactory->createVehicle(vehicle);
}

int Lane::randomValueBetween(int low , int high) 
{
	return rand() % (int)high + (int)low;
}

float Lane::randomValueBetween(float low , float high) 
{
	return rand() % (int)high + (int)low;
}

int Lane::getSpeed()
{
	return _speed;
}

void Lane::increaseSpeed()
{
	_speed = _speed + 100;
}

std::string Lane::getLaneType()
{
	return _type;
}

int Lane::getLaneNumber()
{
	return _laneNumber;
}
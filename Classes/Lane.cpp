#include "Lane.h"
#include "Car.h"
#include "Bus.h"
#include "Truck.h"
#include "Log.h"
#include "DisappearingLog.h"
#include "GameFunctions.h"

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

	_spawnInterval = lane->valueForKey("Interval")->floatValue();
	_spawnIntervalLow = 2000;
	_spawnIntervalHigh = 3000;
	if (_spawnInterval == 0)
	{
		_spawnInterval = GameFunctions::randomValueBetween(_spawnIntervalLow, _spawnIntervalHigh);
	}
	_initialSpawnInterval = _spawnInterval;

	_speed = lane->valueForKey("Speed")->intValue();
	if (_speed == 0)
	{
		_speed = GameFunctions::randomValueBetween(80, 150);
	}
	_initialSpeed = _speed;

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
			_nextSpawnTime = _spawnInterval + currentTime;
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
	int randomIndex = GameFunctions::randomValueBetween(0, _vehicles.size());
	std::string vehicle = _vehicles.at(randomIndex);

	return _vehicleFactory->createVehicle(vehicle);
}

int Lane::getSpeed()
{
	return _speed;
}

//in addition to increasing speed, this should reduce the _interval
//should all of this arithmetic be using floats?  To avoid truncation?
//this seems to be working.  Make sure vehicles can't overtake the ones in front of them.
void Lane::increaseSpeed()
{
	float delta = 0.1;
	_speed = _speed + (_initialSpeed * delta);		//speed increases by delta% of the original speed

	//find the percentage difference between _speed and _initialSpeed
	float factor = _speed / _initialSpeed;
	_spawnInterval = _initialSpawnInterval / factor;
}

std::string Lane::getLaneType()
{
	return _type;
}

int Lane::getLaneNumber()
{
	return _laneNumber;
}
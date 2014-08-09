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

	_interval = lane->valueForKey("Interval")->floatValue();
	if (_interval == 0)
	{
		//get random interval
		_interval = GameFunctions::randomValueBetween(2000, 3000);
	}

	_speed = lane->valueForKey("Speed")->intValue();
	if (_speed == 0)
	{
		//get random speed
		_speed = GameFunctions::randomValueBetween(80, 150);
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
	CCSprite * vehicleSprite = vehicle->getSprite();
	float y = _dimensions->getLanePixelValue(_laneNumber);

	if (_laneNumber % 2 == 0) //move to the left
	{
		vehicleSprite->setPosition(ccp(windowSize.width, y));
		CCPoint destination = ccp(-120, y); //-120 so the sprite goes completely off screen.  TODO: This should be scaled
		vehicle->setDestination(destination);
		if (vehicleSprite->getScaleX() < 0)
			vehicleSprite->setScaleX(vehicleSprite->getScaleX() * -1.f);
	}
	else //move to the right
	{
		vehicleSprite->setPosition(ccp(0, y));
		CCPoint destination = ccp(windowSize.width + 120, y);
		vehicle->setDestination(destination);
		vehicleSprite->setScaleX(vehicleSprite->getScaleX() * -1.f);
		/*
		For quite a while, I was having a problem here with vehicle->getSprite()->setFlippedX().  It would alter the y position of the sprite.
		I still am not quite sure why it did that.  Due to that I decided to flip X with the following:
		vehicle->getSprite()->setScaleX(-1.f);
		That worked, in that it flipped the sprite and did not alter the y position of the sprite.  However, it shortened the x length of
		the sprite.  Ugh, problems!  This occurred because in the class of the specific sprite container (Truck, when I was testing this out)
		I scaled the sprite AND set the appropriate content size.  Thus, the scale was set to something GREATER that 1.  Therefore, setting
		the scale to -1.f flipped the sprite but made it smaller relative to the content size.  The solution was to do this:
		vehicle->getSprite()->setScaleX(vehicle->getSprite()->getScaleX() * -1.f);
		I still need to figure out the intricacies between scaling a sprite and the sprite's content size.
		*/
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
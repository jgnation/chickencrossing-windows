#include "Lane.h"
#include "Car.h"
#include "Bus.h"
#include "Truck.h"
#include "Log.h"
#include "DisappearingLog.h"
#include "GameFunctions.h"

using namespace cocos2d;

Lane::Lane(int laneNumber, LaneType laneType, int interval, float duration, std::vector<std::string> vehicles) 
{
	_laneNumber = laneNumber;
	_laneType = laneType;
	_duration = duration;
	_vehicles = vehicles;
	_interval = interval;

	_nextSpawnTime = 0;

	_vehicleFactory = new VehicleFactory();
	_dimensions = new Dimensions();
}

bool Lane::isTimeToSpawn(float currentTime)
{
	if (_laneType == LaneType::WATER || _laneType == LaneType::ROAD)
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
	CCSprite * vehicleSprite = vehicle->getSprite();
	float y = _dimensions->getLanePixelValue(_laneNumber);
	float vehicleWidth = vehicleSprite->getContentSize().width;

	if (_laneNumber % 2 == 0) //move to the left
	{
		vehicleSprite->setPosition(ccp(windowSize.width, y));
		CCPoint destination = ccp(-(vehicleWidth), y);
		vehicle->setDestination(destination);
		if (vehicleSprite->getScaleX() < 0)
			vehicleSprite->setScaleX(vehicleSprite->getScaleX() * -1.f);
	}
	else //move to the right
	{
		vehicleSprite->setPosition(ccp(0, y));
		CCPoint destination = ccp(windowSize.width + (vehicleWidth), y);
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

	vehicle->setDuration(_duration);

	return vehicle;
}

Vehicle * Lane::getRandomVehicle()
{
	int randomIndex = GameFunctions::randomValueBetween(0, _vehicles.size() - 1);
	std::string vehicle = _vehicles.at(randomIndex);

	return _vehicleFactory->createVehicle(vehicle);
}

int Lane::getSpeed()
{
	return _speed;
}

Lane::LaneType Lane::getLaneType()
{
	return _laneType;
}

int Lane::getLaneNumber()
{
	return _laneNumber;
}

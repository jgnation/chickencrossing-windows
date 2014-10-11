#include "AcceleratingLane.h"

AcceleratingLane::AcceleratingLane(int laneNumber, LaneType laneType, int interval, float duration, float maxDuration, float minDuration, std::vector<std::string> vehicles) 
	: Lane(laneNumber, laneType, interval, duration, vehicles)
{
	_maxDuration = maxDuration;
	_minDuration = minDuration;
}

void AcceleratingLane::increaseSpeed()
{
	if (_duration > _minDuration)
	{
		float difference = _maxDuration - _minDuration;
		float newDuration = _duration - (difference * .1); //increase _duration by 10%

		if (newDuration >= _minDuration)
		{
			this->decreaseInterval(_interval, _duration, newDuration);	
			_duration = newDuration; 
		}
		else
		{
			newDuration = _minDuration;
			this->decreaseInterval(_interval, _duration, newDuration);
			_duration = newDuration;
		}
	}
}

void AcceleratingLane::decreaseInterval(float interval, float currentDuration, float newDuration)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	Vehicle * vehicle = this->getRandomVehicle();
	float vehicleWidth = vehicle->getSprite()->getContentSize().width;
	float distance = ccpDistance(ccp(0, 0), ccp(windowSize.width + vehicleWidth, 0));

	float currentSpeed = distance / currentDuration;
	float distancePerCurrentInterval = currentSpeed * interval;

	float newSpeed = distance / newDuration;
	float newInterval = distancePerCurrentInterval / newSpeed;

	_interval = newInterval;
}

Vehicle * AcceleratingLane::spawnVehicle()
{
	Vehicle * vehicle = Lane::spawnVehicle();
	/*
	if vehicle == disappearingLog, then set the disappearing interval.
	this disappearing interval should be a class variable set by either
	increaseSpeed(), decreaseInterval(), or a function called from
	one of those two functions.

	OR (and this would be better), maybe this can be taken care of
	just in DisappearingLog.  The faster the log is travelling,
	the shorter the disappearing time.
	*/
	return vehicle;
}
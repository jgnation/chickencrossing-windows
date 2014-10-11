#ifndef __ACCELERATING_LANE_H__
#define __ACCELERATING_LANE_H__

#include "Lane.h"

class AcceleratingLane : public Lane
{
public:
	AcceleratingLane(int laneNumber, LaneType laneType, int interval, float duration, float maxDuration, float minDuration, std::vector<std::string> vehicles);
	~AcceleratingLane(void);
	void increaseSpeed();
	Vehicle * spawnVehicle();
private:
	float _maxDuration;
	float _minDuration;

	void decreaseInterval(float interval, float oldDuration, float newDuration);
};

#endif


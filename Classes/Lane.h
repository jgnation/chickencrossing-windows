#ifndef LANE_H
#define LANE_H

#include "cocos2d.h"
#include "Vehicle.h"
#include "VehicleFactory.h"
#include "Dimensions.h"

using namespace cocos2d;

class Lane
{
private:

public:
	enum LaneType { ROAD, WATER, REST, INVALID };

	Lane(int laneNumber, LaneType laneType, int interval, float duration, std::vector<std::string> vehicles);

	~Lane(void);
	LaneType _laneType;
	void setType(std::string type);
	void setVehicles();
	void setInterval(std::string interval);
	void setSpeed(std::string speed);
	bool isTimeToSpawn(unsigned long long currentTime);
	Vehicle * spawnVehicle();
	Vehicle * getRandomVehicle();	//this should be private

	virtual int getSpeed();	

	std::string _type;
	std::vector<std::string> _vehicles;

	float _interval;
	int _speed;
	float _duration;

	unsigned long long _nextSpawnTime;
	int _laneNumber;

	int getLaneNumber();
	LaneType getLaneType();
};

#endif

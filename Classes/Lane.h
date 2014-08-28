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
	VehicleFactory *_vehicleFactory;
	Dimensions * _dimensions;

public:
	enum LaneType { ROAD, WATER, REST, INVALID };

	Lane(int laneNumber, LaneType laneType, int interval, float duration, std::vector<std::string> vehicles);

	~Lane(void);
	LaneType _laneType;
	void setType(std::string type);
	void setVehicles();
	void setInterval(std::string interval);
	void setSpeed(std::string speed);
	bool isTimeToSpawn(float currentTime);
	bool isTimeToIncreaseSpeed(float currentTime);
	Vehicle * spawnVehicle();
	Vehicle * getRandomVehicle();	//this should be private

	int getSpeed();
	void increaseSpeed();

	std::string _type;
	std::vector<std::string> _vehicles;

	float _interval;
	int _speed;
	float _duration;
	float _nextSpawnTime;
	int _laneNumber;
	float _increaseSpeedInterval;
	float _nextIncreaseSpeedTime;

	int getLaneNumber();
	LaneType getLaneType();
};

#endif

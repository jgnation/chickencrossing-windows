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

	int _speed;
	int _initialSpeed;
	float _spawnInterval; //this should probably be an int
	float _initialSpawnInterval;



	int _spawnIntervalLow;
	int _spawnIntervalHigh;
	int _spawnIntervalLowerBound;

	std::string _type;
	std::vector<std::string> _vehicles;

	
	
	float _nextSpawnTime;
	int _laneNumber;
	float _increaseSpeedInterval;
	float _nextIncreaseSpeedTime;
public:
	Lane(CCDictionary * lane, int laneNumber);
	~Lane(void);

	void setType(std::string type);
	void setVehicles();
	void setInterval(std::string interval);
	void setSpeed(std::string speed);
	bool isTimeToSpawn(float currentTime);
	bool isTimeToIncreaseSpeed(float currentTime);
	Vehicle * spawnVehicle();
	Vehicle * getRandomVehicle();
	int getSpeed();
	void increaseSpeed();
	int getLaneNumber();
	std::string getLaneType();
};

#endif
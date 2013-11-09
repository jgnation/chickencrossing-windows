#ifndef LANE_H
#define LANE_H

#include "cocos2d.h"
#include "Vehicle.h"

using namespace cocos2d;

class Lane
{
public:
	Lane(CCDictionary * lane, int laneNumber);

	~Lane(void);

	void setType(std::string type);
	void setVehicles();
	void setInterval(std::string interval);
	void setSpeed(std::string speed);
	bool isTimeToSpawn(float currentTime);
	Vehicle * spawnVehicle();
	Vehicle * getRandomVehicle();	//this should be private
	int randomValueBetween(int low , int high); //private

	int getSpeed();
	float getY();

	std::string _type;
	std::vector<std::string> _vehicles;

	float _interval;
	int _speed;
	float _nextSpawnTime;
	int _laneNumber;

	float _y;


	float getLanePixelPosition(int laneNumber);
};

#endif
#include "Level.h"
#include "GameFunctions.h"

using namespace cocos2d;

Level::Level(CCDictionary * levelData)
{
	_levelData = levelData;
	_background = new Background(_levelData->valueForKey("Background")->getCString());
	int maxRoadInterval = _levelData->valueForKey("MaxRoadInterval")->intValue();
	int minRoadInterval = _levelData->valueForKey("MinRoadInterval")->intValue();
	int maxWaterInterval = _levelData->valueForKey("MaxWaterInterval")->intValue();
	int minWaterInterval = _levelData->valueForKey("MinWaterInterval")->intValue();
	float minStartDuration = _levelData->valueForKey("MinStartDuration")->floatValue();
	float maxStartDuration = _levelData->valueForKey("MaxStartDuration")->floatValue();
	float maxDuration = _levelData->valueForKey("MaxDuration")->floatValue();
	float minDuration = _levelData->valueForKey("MinDuration")->floatValue();

	CCArray * lanes = (CCArray *) _levelData->objectForKey("Lanes");

	int laneNumber = 1; //natural indeces
	CCObject *it;
	CCARRAY_FOREACH(lanes, it)
	{
		CCDictionary * lane = dynamic_cast<CCDictionary *>(it);

		Lane::LaneType laneType = this->getLaneType(laneNumber);

		int interval;
		if (laneType == Lane::LaneType::ROAD)
			interval = GameFunctions::randomValueBetween(minRoadInterval, maxRoadInterval);
		else if (laneType == Lane::LaneType::WATER)
			interval = GameFunctions::randomValueBetween(minWaterInterval, maxWaterInterval);
		else
			interval = 0;

		float duration = GameFunctions::randomValueBetween(minStartDuration, maxStartDuration);

		CCArray * vehicles = (CCArray *) lane->objectForKey("Vehicles");
		CCObject *iter;
		std::vector<std::string> vehicleVector;
		CCARRAY_FOREACH(vehicles, iter)
		{
			CCString * vehicle = dynamic_cast<CCString *>(iter);
			vehicleVector.push_back(vehicle->getCString());
		}

		_lanes.push_back(new Lane(laneNumber, laneType, interval, duration, maxDuration, minDuration, vehicleVector));
		laneNumber++;
	}
}

Background * Level::getBackground()
{
	return _background;
}

std::vector<Lane *> Level::getLanes()
{
	return _lanes;
}

Lane * Level::getLane(int laneNumber)
{
	laneNumber--; //the index of the items in the file are 1 less than I am using in the program
	//I am using 'natural indeces'

	return _lanes[laneNumber];
}

void Level::increaseSpeed()
{
	for(std::vector<Lane *>::iterator it = _lanes.begin(); it != _lanes.end(); ++it) 
	{
		Lane * lane = dynamic_cast<Lane *>(*it);
		Lane::LaneType laneType = lane->getLaneType();
		if (laneType == Lane::LaneType::ROAD || laneType == Lane::LaneType::WATER)
		{
			lane->increaseSpeed();
		}		
	}
}

//TODO: cache the lane value so I don't have to parse the XML every time this is called
Lane::LaneType Level::getLaneType(int laneNumber)
{
	laneNumber--; //the index of the items in the file are 1 less than I am using in the program
	//I am using 'natural indeces'

	CCArray * lanes = (CCArray *) _levelData->objectForKey("Lanes");
	CCDictionary * lane = (CCDictionary *) lanes->objectAtIndex(laneNumber);
	CCString * laneType = (CCString *) lane->objectForKey("Type");
	std::string laneTypeString = laneType->getCString();

	Lane::LaneType laneEnumType;
	if (laneTypeString == "INVALID")
		laneEnumType = Lane::LaneType::INVALID;
	else if (laneTypeString == "REST")
		laneEnumType = Lane::LaneType::REST;
	else if (laneTypeString == "ROAD")
		laneEnumType = Lane::LaneType::ROAD;
	else // == WATER
		laneEnumType = Lane::LaneType::WATER;

	return laneEnumType;
}

/**blahblahblah
*/
int Level::getRandomValidLaneNumber()
{
	//this is what GameLayer currently does
	//int validLanes[10] = {3, 4, 5, 6, 7, 9, 10, 11, 12, 13};
	//return (int)randomValueBetween(0.0, 9.0);

	//get list of VALID lanes (lanes where type != INVALID or REST)
	//return random value from that list

	//iterate through _lanes...if _lanes->type != invlaid or rest, then add _laneNumber to a vector
	std::vector<int> validLaneNumbers;
	for(std::vector<Lane *>::iterator it = _lanes.begin(); it != _lanes.end(); ++it) 
	{
		Lane * lane = dynamic_cast<Lane *>(*it);
		if (lane->getLaneType() != Lane::LaneType::INVALID && lane->getLaneType() != Lane::LaneType::REST)
		{
			validLaneNumbers.push_back(lane->getLaneNumber());
		}
	}
	//get random value between 0 and length of vector-1....to get a random index of that
	int randomIndex = GameFunctions::randomValueBetween(0, validLaneNumbers.size() - 1);
	return validLaneNumbers[randomIndex];
}


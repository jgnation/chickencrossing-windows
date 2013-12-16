#include "Level.h"
#include "GameFunctions.h"

using namespace cocos2d;

Level::Level(CCDictionary * levelData)
{
	_levelData = levelData;
	_background = new Background(_levelData->valueForKey("Background")->getCString());

	CCArray * lanes = (CCArray *) _levelData->objectForKey("Lanes");

	int laneNumber = 1; //natural indeces
	CCObject *it;
	CCARRAY_FOREACH(lanes, it)
	{
		CCDictionary * lane = dynamic_cast<CCDictionary *>(it);
		_lanes.push_back(new Lane(lane, laneNumber));
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

Level::LaneType Level::getLaneType(int laneNumber)
{
	laneNumber--; //the index of the items in the file are 1 less than I am using in the program
	//I am using 'natural indeces'

	CCArray * lanes = (CCArray *) _levelData->objectForKey("Lanes");
	CCDictionary * lane = (CCDictionary *) lanes->objectAtIndex(laneNumber);
	CCString * laneType = (CCString *) lane->objectForKey("Type");
	std::string laneTypeString = laneType->getCString();

	LaneType laneEnumType;
	if (laneTypeString == "INVALID")
		laneEnumType = Level::LaneType::INVALID;
	else if (laneTypeString == "REST")
		laneEnumType = Level::LaneType::REST;
	else if (laneTypeString == "ROAD")
		laneEnumType = Level::LaneType::ROAD;
	else // == WATER
		laneEnumType = Level::LaneType::WATER;

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
		if (lane->getLaneType() != "INVALID" && lane->getLaneType() != "REST")
		{
			validLaneNumbers.push_back(lane->getLaneNumber());
		}
	}
	//get random value between 0 and length of vector-1....to get a random index of that
	int randomIndex = GameFunctions::randomValueBetween(0, validLaneNumbers.size());
	return validLaneNumbers[randomIndex];
}


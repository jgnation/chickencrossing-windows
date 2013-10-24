#include "Level1.h"
#include <map>

Level1::Level1(void)
{
	_background = new Background("background1.png");

	_lanes[1] = INVALID;
	_lanes[2] = REST;
	_lanes[3] = ROAD;
	_lanes[4] = ROAD;
	_lanes[5] = ROAD;
	_lanes[6] = ROAD;
	_lanes[7] = ROAD;
	_lanes[8] = REST;
	_lanes[9] = ROAD;
	_lanes[10] = ROAD;
	_lanes[11] = ROAD;
	_lanes[12] = ROAD;
	_lanes[13] = ROAD;
	_lanes[14] = REST;
	_lanes[15] = INVALID;
	_lanes[16] = INVALID;
}

Level::LaneType Level1::getLaneType(int laneNumber)
{
	return _lanes[laneNumber];
}

void Level1::update()
{
}
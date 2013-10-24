#include "Level2.h"


Level2::Level2(void)
{
	_background = new Background("background2.png");

	_lanes[1] = INVALID;
	_lanes[2] = REST;
	_lanes[3] = ROAD;
	_lanes[4] = ROAD;
	_lanes[5] = ROAD;
	_lanes[6] = ROAD;
	_lanes[7] = ROAD;
	_lanes[8] = REST;
	_lanes[9] = WATER;
	_lanes[10] = WATER;
	_lanes[11] = WATER;
	_lanes[12] = WATER;
	_lanes[13] = WATER;
	_lanes[14] = REST;
	_lanes[15] = INVALID;
	_lanes[16] = INVALID;
}

Level::LaneType Level2::getLaneType(int laneNumber)
{
	return _lanes[laneNumber];
}

void Level2::update()
{
}
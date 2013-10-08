#ifndef __LEVEL_H__
#define __LEVEL_H__
 
#include "cocos2d.h"
#include "Background.h"
 
using namespace cocos2d;

class Level
{
public:
	enum LaneType { ROAD, WATER, REST, INVALID };

	//Level();
	//~Level();
    virtual LaneType getLaneType(int laneNumber) = 0; //the = 0 makes it a 'pure' virtual function
    Background * getBackground();

protected:
    Background * _background;
	std::map<int, LaneType> _lanes;
	/*
	 For some reason the _lanes map had to be declared BELOW the enum, otherwise it was 'undefined'.  Forward declaration wouldn't work.
	 It caused a strange error in Level1.cpp.
	*/

};
 
#endif // __LEVEL_H__
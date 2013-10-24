#ifndef __LEVEL2_H__
#define __LEVEL2_H__
 
#include "cocos2d.h"
#include "Background.h"
#include "Level.h"

using namespace cocos2d;

class Level2 : public Level
{
public:
	Level2();
	~Level2();
    LaneType getLaneType(int laneNumber);
	void update();
};
 
#endif // __LEVEL2_H__
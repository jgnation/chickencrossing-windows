#ifndef __LEVEL1_H__
#define __LEVEL1_H__
 
#include "cocos2d.h"
#include "Background.h"
#include "Level.h"

using namespace cocos2d;

class Level1 : public Level
{
public:
	Level1();
	~Level1();
    LaneType getLaneType(int laneNumber);
	void update();
};
 
#endif // __LEVEL1_H__
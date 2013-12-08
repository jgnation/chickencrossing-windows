#ifndef __GAME_MODE_H__
#define __GAME_MODE_H__

#include "cocos2d.h"
#include "GameLayer.h"

class GameMode
{
public:
	GameMode();
	~GameMode();
	virtual void initialLoopInstructions(GameLayer * gameLayer);
};
#endif
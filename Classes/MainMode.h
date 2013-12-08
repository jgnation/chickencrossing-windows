#ifndef __MAIN_MODE_H__
#define __MAIN_MODE_H__

#include "GameMode.h"
#include "GameLayer.h"

class MainMode : public GameMode
{
public:
	MainMode(void);
	~MainMode(void);
	virtual void initialLoopInstructions(GameLayer * gameLayer);
};

#endif


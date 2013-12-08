#ifndef __EGG_SCRAMBLE_MODE_H__
#define __EGG_SCRAMBLE_MODE_H__

#include "GameMode.h"
#include "GameLayer.h"

class EggScrambleMode :	public GameMode
{
public:
	EggScrambleMode(int levelNumber);
	~EggScrambleMode(void);

	virtual void initialLoopInstructions(GameLayer * gameLayer);
};

#endif


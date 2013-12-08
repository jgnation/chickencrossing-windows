#include "MainMode.h"


MainMode::MainMode(void)
{
}


MainMode::~MainMode(void)
{
}

void MainMode::initialLoopInstructions(GameLayer * gameLayer)
{
	if (gameLayer->_score >= gameLayer->_numEggsToCollect)
	{
		gameLayer->loadNextLevel();
	}
}

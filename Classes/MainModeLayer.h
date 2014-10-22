#ifndef __MAIN_MODE_LAYER_H__
#define __MAIN_MODE_LAYER_H__

#include "GameLayer.h"

class MainModeLayer : public GameLayer
{
protected:
	int _nextLevelScore;
public:
	MainModeLayer(void);
	~MainModeLayer(void);

	void initialChecks();
	std::vector<TopScore> checkHighScores();

	//virtual bool init();
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(MainModeLayer);
};

#endif


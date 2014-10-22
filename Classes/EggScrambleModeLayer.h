#ifndef __EGG_SCRAMBLE_MODE_LAYER_H__
#define __EGG_SCRAMBLE_MODE_LAYER_H__

#include "GameLayer.h"
//#include "TopScore.h"

class EggScrambleModeLayer : public GameLayer
{
public:
	EggScrambleModeLayer(void);
	~EggScrambleModeLayer(void);

	void initialChecks();
	std::vector<TopScore> checkHighScores();

	//virtual bool init();
	//static cocos2d::CCScene* scene();
	//CREATE_FUNC(EggScrambleModeLayer);

		//The following 3 items are overriding CCLayer's methods....or is it redefining?
	//technically....I think I am overLOADING
	static cocos2d::CCScene* scene(int levelNumber);
	static EggScrambleModeLayer* create(int levelNumber);
	virtual bool init(int levelNumber);
};

#endif


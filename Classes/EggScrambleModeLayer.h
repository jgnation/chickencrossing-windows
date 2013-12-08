#ifndef __EGG_SCRAMBLE_MODE_LAYER_H__
#define __EGG_SCRAMBLE_MODE_LAYER_H__

#include "GameLayer.h"

class EggScrambleModeLayer : public GameLayer
{
public:
	EggScrambleModeLayer(void);
	~EggScrambleModeLayer(void);

	void initialChecks();

	//virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(EggScrambleModeLayer);
};

#endif


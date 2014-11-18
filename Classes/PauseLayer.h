#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class PauseLayer : public cocos2d::CCLayer
{
public:
	//PauseLayer(void);
	//~PauseLayer(void);
	virtual bool init();
    static CCScene* scene();
	CREATE_FUNC(PauseLayer);
	void createResumeButton();
	void resume(CCObject* pSender);
};

#endif


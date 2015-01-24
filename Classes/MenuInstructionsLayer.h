#ifndef __MENU_INSTRUCTIONS_LAYER_H__
#define __MENU_INSTRUCTIONS_LAYER_H__

#include "cocos2d.h"
 
using namespace cocos2d;

class MenuInstructionsLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(MenuInstructionsLayer);
	virtual bool init();
	void createInstructionScreen();
	CCMenuItemImage* createInstructionsExitButton();
	void instructionsExitCallback(CCObject* pSender);
};

#endif


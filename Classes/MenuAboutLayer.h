#ifndef __MENU_ABOUT_LAYER_H__
#define __MENU_ABOUT_LAYER_H__

#include "cocos2d.h"
 
using namespace cocos2d;

class MenuAboutLayer : public cocos2d::Layer
{
private:
	CCLabelBMFont * _aboutInfo;

public:
	CREATE_FUNC(MenuAboutLayer);
	virtual bool init();

	void createAboutScreen();
	void createAboutScreenInfo();
	CCMenuItemImage* createJGNationLogo();
	CCMenuItemImage* createAboutExitButton();
	void aboutExitCallback(CCObject* pSender);
	void animateCredits();
};

#endif


#ifndef __MENU_BUTTON_LAYER_H__
#define __MENU_BUTTON_LAYER_H__

#include "cocos2d.h"
 
using namespace cocos2d;

class MenuButtonLayer : public cocos2d::CCLayer
{
private:
	CCSprite * _titleImage;
    CCMenu* _mainMenu;
	CCMenuItemImage* _aboutExitImage;
	CCMenuItemImage* _instructionsExitImage;
	CCMenuItemImage* _logoImage;
	CCSprite* _chickenCrossingInstructionsImage;
	CCLayerColor* _backgroundColor;
	CCLayerColor* _instructionsBackgroundColor;
	CCLabelBMFont * _aboutInfo;
 
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
 
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MenuButtonLayer);

    void startGameCallback(CCObject* pSender);
	void eggScrambleCallback(CCObject* pSender);
	void aboutCallback(CCObject* pSender);
	void aboutExitCallback(CCObject* pSender);
	void instructionsCallback(CCObject* pSender);
	void instructionsExitCallback(CCObject* pSender);
	void purchaseCallback(CCObject* pSender);
 
	CCMenuItemImage* createStartGameButton();
	CCMenuItemImage* createEggScrambleButton();
	CCMenuItemImage* createAboutButton();
	CCMenuItemImage* createAboutExitButton();
	CCMenuItemImage* createInstructionsButton();
	CCMenuItemImage* createInstructionsExitButton();
	CCMenuItemImage* createJGNationLogo();
	CCMenuItemImage* createPurchaseButton();

	void createAboutScreen();
	void createAboutScreenInfo();
	void createInstructionScreen();
};
 
#endif // __MENU_BUTTON_LAYER_H__
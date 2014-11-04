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
	CCSprite* _chickenCrossingAboutImage;
	CCSprite* _chickenCrossingInstructionsImage;
	CCLayerColor* _backgroundColor;
	CCLayerColor* _instructionsBackgroundColor;
 
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
 
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();

 
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MenuButtonLayer);


    void startGameCallback(CCObject* pSender);
	void eggScrambleCallback(CCObject* pSender);
	void aboutCallback(CCObject* pSender);
	void aboutExitCallback(CCObject* pSender);
	void instructionsCallback(CCObject* pSender);
	void instructionsExitCallback(CCObject* pSender);
 
	CCMenuItemImage* createStartGameButton();
	CCMenuItemImage* createEggScrambleButton();
	CCMenuItemImage* createAboutButton();
	CCMenuItemImage* createAboutExitButton();
	CCMenuItemImage* createInstructionsButton();
	CCMenuItemImage* createInstructionsExitButton();
	CCMenuItemImage* createJGNationLogo();

	void createAboutScreen();
	void createInstructionScreen();
};
 
#endif // __MENU_BUTTON_LAYER_H__
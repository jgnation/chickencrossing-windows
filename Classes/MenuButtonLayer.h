#ifndef __MENU_BUTTON_LAYER_H__
#define __MENU_BUTTON_LAYER_H__

#include "cocos2d.h"
#include "MenuStoreLayer.h"
#include "MenuAboutLayer.h"
#include "MenuInstructionsLayer.h"
 
using namespace cocos2d;

class MenuButtonLayer : public cocos2d::CCLayer
{
private:
	CCSprite * _titleImage;
    CCMenu* _mainMenu;
	CCLayerColor* _backgroundColor;

	MenuStoreLayer * _menuStoreLayer;
	MenuAboutLayer * _menuAboutLayer;
	MenuInstructionsLayer * _menuInstructionsLayer;

	CCMenuItemImage* _muteImage;
	CCMenuItemImage* _unmuteImage;
 
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
 
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MenuButtonLayer);

    void startGameCallback(CCObject* pSender);
	void eggScrambleCallback(CCObject* pSender);
	void aboutCallback(CCObject* pSender);
	void instructionsCallback(CCObject* pSender);
	void purchaseCallback(CCObject* pSender);
	void muteCallback(CCObject* pSender);
	void unmuteCallback(CCObject* pSender);
 
	CCMenuItemImage* createStartGameButton();
	CCMenuItemImage* createEggScrambleButton();
	CCMenuItemImage* createAboutButton();
	CCMenuItemImage* createInstructionsButton();
	CCMenuItemImage* createPurchaseButton();
	CCMenuItemImage* createMuteButton();
	CCMenuItemImage* createUnmuteButton();

	void resetDisplay();
};
 
#endif // __MENU_BUTTON_LAYER_H__
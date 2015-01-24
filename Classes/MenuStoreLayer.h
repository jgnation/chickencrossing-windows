#ifndef __MENU_STORE_LAYER_H__
#define __MENU_STORE_LAYER_H__

#include "cocos2d.h"
 
using namespace cocos2d;

class MenuStoreLayer : public cocos2d::Layer
{
private:
	CCMenu* _mainMenu;
public:
	CREATE_FUNC(MenuStoreLayer);
	virtual bool init();

	CCMenuItemImage* createPurchaseButton();
	void makePurchase(CCObject* pSender);

	void getStoreData();
	void storeDataCallback(std::string price);

	void createLoadingLabel();
};

#endif


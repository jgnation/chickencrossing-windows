#ifndef __MENU_STORE_LAYER_H__
#define __MENU_STORE_LAYER_H__

#include "cocos2d.h"
 
using namespace cocos2d;

class MenuStoreLayer : public cocos2d::Layer
{
private:
	CCMenu* _buyMenu;
	CCMenu* _exitMenu;
	CCMenu* _retryMenu;
	CCSprite* _loadingSprite;
	CCSprite* _purchaseTitleImage;
	CCLabelTTF* _failureLabel;
    CCLabelTTF* _premiumLabel;
    CCLabelTTF* _descriptionLabel;
    bool _storeLoaded;
public:
	CREATE_FUNC(MenuStoreLayer);
	virtual bool init();

	void buy(CCObject* pSender);
	void restore(CCObject* pSender);
	void exit(CCObject* pSender);

	void getStoreData();

	void createPurchaseTitleImage();
	CCMenuItemImage* createBuyButton();
	CCMenuItemImage* createRestoreButton();
	CCMenuItemImage* createExitButton();
    
    void loadStore();
    void loadStoreSuccessCallback(std::string formattedPrice);
    void loadStoreFailureCallback();

	void createLoadingSprite();

	void createLoadingFailureLabel();
    void createPremiumLabel();
    
	CCMenuItemImage* createRetryButton();
	void retry(CCObject* pSender);
    
    void createDescriptionLabel();
};

#endif


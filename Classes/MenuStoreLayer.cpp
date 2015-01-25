#include "MenuStoreLayer.h"
#include "PurchaseHelper.h"
#include "MenuButtonLayer.h"

using namespace cocos2d;

bool MenuStoreLayer::init()
{
	bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		this->createLoadingSprite();

		//create exit button
		CCMenuItemImage * exitImage = this->createExitButton();
		_exitMenu = CCMenu::create(exitImage, NULL);
		_exitMenu->setPosition(CCPointZero);
		this->addChild(_exitMenu);

        //create and hide this stuff
		//this->createPurchaseTitleImage();
		//_purchaseTitleImage->setVisible(false);
		
		//create buy/restore buttons
		CCMenuItemImage * buyImage = this->createBuyButton();
		CCMenuItemImage * restoreImage = this->createRestoreButton();		
		_buyMenu = CCMenu::create(buyImage,	restoreImage, NULL);
		_buyMenu->setPosition(CCPointZero);
		this->addChild(_buyMenu);
		_buyMenu->setVisible(false);

		//create failed label
		this->createLoadingFailureLabel();
		//_failureLabel->setVisible(false);

		//create retry menu
		CCMenuItemImage * retryImage = this->createRetryButton();
		_retryMenu = CCMenu::create(retryImage, NULL);
		_retryMenu->setPosition(CCPointZero);
		this->addChild(_retryMenu);
		//_retryMenu->setVisible(true);

		

		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isPremium"))
		{
			//display "you already own premium!"
		}
		else
		{
			//create and display "loading..." image

			//fire off request to get store data
			//this->getStoreData();
		}

		bRet = true;
    } while (0);

    return bRet;
}

void MenuStoreLayer::loadStore()
{
    PurchaseHelper::getStoreData();
    //if !loaded
    //send request to ObjC to get products
    //ObjC should store the products after a single request is made, so only one will ever be needed
    //if products sucessfully load (or already exist in Objc code), hit a callback in here
    //in callabck, hide loading... and display store
    
    //if loaded, hide loading... and display store
}

void MenuStoreLayer::loadStoreSuccessCallback()
{
    //TODO: set loaded to true
    
	_loadingSprite->setVisible(false);
	_buyMenu->setVisible(true);
	_purchaseTitleImage->setVisible(true);
}

void MenuStoreLayer::loadStoreFailureCallback()
{
    //display error and retry button
	_loadingSprite->setVisible(false);
}

void MenuStoreLayer::createPurchaseTitleImage()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	float originalWidth = 670;
	float originalHeight = 144;
	_purchaseTitleImage = CCSprite::create("purchase_ad_removal_orange.png", CCRectMake(0, 0, originalWidth, originalHeight));        
	float scaleRatio = (windowSize.width *.6) / _purchaseTitleImage->getContentSize().width;
	_purchaseTitleImage->setScale(scaleRatio);
	_purchaseTitleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
	this->addChild(_purchaseTitleImage);
}

CCMenuItemImage* MenuStoreLayer::createBuyButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 400;
	float originalHeight = 200;

	CCMenuItemImage *purchaseImage = CCMenuItemImage::create(
		"Buy.png",
		"Buy.png",
		this,
		menu_selector(MenuStoreLayer::buy));

	float scaleRatio = (windowSize.width *.3) / purchaseImage->getContentSize().width;
	purchaseImage->setScale(scaleRatio);
	purchaseImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width * .3, CCDirector::sharedDirector()->getWinSize().height * .4));

	return purchaseImage;
}

void MenuStoreLayer::buy(CCObject* pSender)
{
	PurchaseHelper::makePurchase();
}

CCMenuItemImage* MenuStoreLayer::createRestoreButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 400;
	float originalHeight = 200;

	CCMenuItemImage *purchaseImage = CCMenuItemImage::create(
		"Restore.png",
		"Restore.png",
		this,
		menu_selector(MenuStoreLayer::restore));

	float scaleRatio = (windowSize.width *.3) / purchaseImage->getContentSize().width;
	purchaseImage->setScale(scaleRatio);
	purchaseImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width * .7, CCDirector::sharedDirector()->getWinSize().height * .4));

	return purchaseImage;
}

void MenuStoreLayer::restore(CCObject* pSender)
{
    PurchaseHelper::restorePurchase();
}

CCMenuItemImage* MenuStoreLayer::createExitButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 300;
	float originalHeigh = 228;

	CCMenuItemImage * arrow = CCMenuItemImage::create(
		"arrow_left.png",
		"arrow_left.png",
		this,
		menu_selector(MenuStoreLayer::exit));

	float scaleRatioArrowX = (windowSize.width *.2) / arrow->getContentSize().width;
	float scaleRatioArrowY = (windowSize.height *.15) / arrow->getContentSize().height;
	arrow->setScale(scaleRatioArrowX);
	arrow->setScale(scaleRatioArrowY);
	arrow->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .20));

	return arrow;
}

void MenuStoreLayer::exit(CCObject* pSender)
{
	Node * parent = this->getParent();
	MenuButtonLayer* menuButtonLayer = dynamic_cast<MenuButtonLayer*>(parent);
	if(menuButtonLayer != 0)
	{
		menuButtonLayer->resetDisplay();
	}
}

CCMenuItemImage* MenuStoreLayer::createRetryButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 400;
	float originalHeight = 200;

	CCMenuItemImage *purchaseImage = CCMenuItemImage::create(
		"Retry.png",
		"Retry.png",
		this,
		menu_selector(MenuStoreLayer::retry));

	float scaleRatio = (windowSize.width *.3) / purchaseImage->getContentSize().width;
	purchaseImage->setScale(scaleRatio);
	purchaseImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .4));

	return purchaseImage;
}

void MenuStoreLayer::retry(CCObject* pSender)
{
	_buyMenu->setVisible(false);
	_loadingSprite->setVisible(true);
}

/*
I envision this calling into iOS/Android and getting the formatted price back eventually.
The iOS/Android controller/activity can make the request and store the data.
If the data is stored (i.e. a request has already been made), then there is no need to make a second request
*/
void MenuStoreLayer::getStoreData()
{
	PurchaseHelper::getStoreData();
}

void MenuStoreLayer::createLoadingSprite()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	//add title image
	float originalWidth = 670;
	float originalHeight = 144;
	_loadingSprite = CCSprite::create("requesting_store_data.png", CCRectMake(0, 0, originalWidth, originalHeight));
        
	float scaleRatio = (windowSize.width *.7) / _loadingSprite->getContentSize().width;
	_loadingSprite->setScale(scaleRatio);
	_loadingSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
	this->addChild(_loadingSprite);
}

void MenuStoreLayer::createLoadingFailureLabel()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
    _failureLabel = CCLabelTTF::create("Failed to load store data.\nCheck your network connection.", "Verdana-Bold", 60.0); 
    _failureLabel->setColor(ccc3(255,0,0));

	float scaleRatio = (winSize.width *.7) / _failureLabel->getContentSize().width;
	_failureLabel->setScale(scaleRatio);
	_failureLabel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
    this->addChild(_failureLabel);
}
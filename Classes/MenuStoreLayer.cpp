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

		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isPremium"))
		{
            this->createPremiumLabel();
            _premiumLabel->setVisible(true);
			_premiumBackgroundColor->setVisible(true);
		}
		else
		{
            _storeLoaded = false;
            
            this->createLoadingSprite();
            
            //create and hide this stuff
            this->createPurchaseTitleImage();
            _purchaseTitleImage->setVisible(false);
            
            //create buy/restore buttons
            CCMenuItemImage * buyImage = this->createBuyButton();
            CCMenuItemImage * restoreImage = this->createRestoreButton();
            _buyMenu = CCMenu::create(buyImage,	restoreImage, NULL);
            _buyMenu->setPosition(ccp(0,0));
            this->addChild(_buyMenu);
            _buyMenu->setVisible(false);
            
            this->createDescriptionLabel();
            _descriptionLabel->setVisible(false);
			_descriptionBackgroundColor->setVisible(false);
            
            //create failed label
            this->createLoadingFailureLabel();
            _failureLabel->setVisible(false);
			_failureBackgroundColor->setVisible(false);
            
            //create retry menu
            CCMenuItemImage * retryImage = this->createRetryButton();
            _retryMenu = CCMenu::create(retryImage, NULL);
            _retryMenu->setPosition(ccp(0,0));
            this->addChild(_retryMenu);
            _retryMenu->setVisible(false);
		}
        
        //create exit button
        CCMenuItemImage * exitImage = this->createExitButton();
        _exitMenu = CCMenu::create(exitImage, NULL);
        _exitMenu->setPosition(ccp(0,0));
        this->addChild(_exitMenu);

		bRet = true;
    } while (0);

    return bRet;
}

void MenuStoreLayer::loadStore()
{
    if(!(CCUserDefault::sharedUserDefault()->getBoolForKey("isPremium")))
    {
        if (_storeLoaded)
        {
            //hide everything I don't need
            _retryMenu->setVisible(false);
            _failureLabel->setVisible(false);
			_failureBackgroundColor->setVisible(false);
            _loadingSprite->setVisible(false);
        
            //show what I need
            _purchaseTitleImage->setVisible(true);
            _buyMenu->setVisible(true);
            _descriptionLabel->setVisible(true);
			_descriptionBackgroundColor->setVisible(true);
        }
        else
        {
            //hide everything I don't need
            _retryMenu->setVisible(false);
            _failureLabel->setVisible(false);
			_failureBackgroundColor->setVisible(false);
            _purchaseTitleImage->setVisible(false);
            _buyMenu->setVisible(false);
            _descriptionLabel->setVisible(false);
			_descriptionBackgroundColor->setVisible(false);
        
            //show what I need
            _loadingSprite->setVisible(true);
            
            PurchaseHelper::getStoreData();
            //if !loaded
            //send request to ObjC to get products
            //ObjC should store the products after a single request is made, so only one will ever be needed
            //if products sucessfully load (or already exist in Objc code), hit a callback in here
            //in callabck, hide loading... and display store
        
            //if loaded, hide loading... and display store
        }
    }
}

void MenuStoreLayer::loadStoreSuccessCallback(std::string formattedPrice)
{
    _storeLoaded = true;
    
	_loadingSprite->setVisible(false);
    
    //TODO: scale the CCLabelTTF?
    CCString * descriptionString = CCString::createWithFormat("Get the full, ad-free version of Egg Scramble,\nand support the developer!\nCost: %s", formattedPrice.c_str());
    _descriptionLabel->setString(descriptionString->getCString());
    
    _descriptionLabel->setVisible(true);
	_descriptionBackgroundColor->setVisible(true);
	_buyMenu->setVisible(true);
	_purchaseTitleImage->setVisible(true);
}

void MenuStoreLayer::loadStoreFailureCallback()
{
    //display error and retry button
	_loadingSprite->setVisible(false);
    _failureLabel->setVisible(true);
	_failureBackgroundColor->setVisible(true);
    _retryMenu->setVisible(true);
}

void MenuStoreLayer::createPurchaseTitleImage()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	float originalWidth = 670;
	float originalHeight = 144;
	_purchaseTitleImage = CCSprite::create("purchase_ad_removal_orange.png", CCRectMake(0, 0, originalWidth, originalHeight));        
	float scaleRatio = (windowSize.width *.6) / _purchaseTitleImage->getContentSize().width;
	_purchaseTitleImage->setScale(scaleRatio);
	_purchaseTitleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .75));
	this->addChild(_purchaseTitleImage);
}

CCMenuItemImage* MenuStoreLayer::createBuyButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 400;
	float originalHeight = 200;

	CCMenuItemImage *purchaseImage = CCMenuItemImage::create(
		"Buy.png",
		"Buy_down.png",
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
		"Restore_down.png",
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
		"Retry_down.png",
		this,
		menu_selector(MenuStoreLayer::retry));

	float scaleRatio = (windowSize.width *.3) / purchaseImage->getContentSize().width;
	purchaseImage->setScale(scaleRatio);
	purchaseImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .4));

	return purchaseImage;
}

void MenuStoreLayer::retry(CCObject* pSender)
{
    this->loadStore();
}

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
    this->addChild(_failureLabel, 2);

	Size labelSize = _failureLabel->getContentSize();
	_failureBackgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), labelSize.width, labelSize.height);
	_failureBackgroundColor->setOpacity(200);
	_failureBackgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
	_failureBackgroundColor->setPosition(_failureLabel->getPosition());
	this->addChild(_failureBackgroundColor, 1);
}

void MenuStoreLayer::createPremiumLabel()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _premiumLabel = CCLabelTTF::create("You already own the full, ad-free game.\nThank you!", "Verdana-Bold", 70.0);
    _premiumLabel->setColor(ccc3(0,0,0));
    
    float scaleRatio = (winSize.width *.7) / _premiumLabel->getContentSize().width;
    _premiumLabel->setScale(scaleRatio);
    _premiumLabel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
    this->addChild(_premiumLabel, 2);

	Size labelSize = _premiumLabel->getContentSize();
	_premiumBackgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), labelSize.width, labelSize.height);
	_premiumBackgroundColor->setOpacity(200);
	_premiumBackgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
	_premiumBackgroundColor->setPosition(_premiumLabel->getPosition());
	this->addChild(_premiumBackgroundColor, 1);
}

void MenuStoreLayer::createDescriptionLabel()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _descriptionLabel = CCLabelTTF::create("Get the full, ad-free version of Egg Scramble,\nand support the developer!\nCost: X", "Verdana-Bold", 50.0);
    _descriptionLabel->setColor(ccc3(0,0,0));
    
    float scaleRatio = (winSize.width *.7) / _descriptionLabel->getContentSize().width;
    _descriptionLabel->setScale(scaleRatio);
    _descriptionLabel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .6));   
    this->addChild(_descriptionLabel, 2);

	Size labelSize = _descriptionLabel->getContentSize();
	_descriptionBackgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), labelSize.width, labelSize.height);
	_descriptionBackgroundColor->setOpacity(200);
	_descriptionBackgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
	_descriptionBackgroundColor->setPosition(_descriptionLabel->getPosition());
	this->addChild(_descriptionBackgroundColor, 1);
}
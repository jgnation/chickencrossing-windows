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

        //display loading image
        //hide the rest of this stuff
		this->createPurchaseTitleImage();
		
		CCMenuItemImage * buyImage = this->createBuyButton();
		CCMenuItemImage * restoreImage = this->createRestoreButton();
		CCMenuItemImage * exitImage = this->createExitButton();
		CCMenu * menu = CCMenu::create(
			buyImage,
			restoreImage,
			exitImage,
			NULL
		);
		menu->setPosition(CCPointZero);
		this->addChild(menu);

		//this->createLoadingLabel();

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
    int x = 43;
    x = 46;
    //set loaded to true
    //
}

void MenuStoreLayer::loadStoreFailureCallback()
{
    int x = 43;
    x = 46;
    //display error and retry button
}

void MenuStoreLayer::createPurchaseTitleImage()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	float originalWidth = 670;
	float originalHeight = 144;
	CCSprite * purchase_title_image = CCSprite::create("purchase_ad_removal_orange.png", CCRectMake(0, 0, originalWidth, originalHeight));        
	float scaleRatio = (windowSize.width *.6) / purchase_title_image->getContentSize().width;
	purchase_title_image->setScale(scaleRatio);
	purchase_title_image->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
	this->addChild(purchase_title_image);
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

/*
I envision this calling into iOS/Android and getting the formatted price back eventually.
The iOS/Android controller/activity can make the request and store the data.
If the data is stored (i.e. a request has already been made), then there is no need to make a second request
*/
void MenuStoreLayer::getStoreData()
{
	PurchaseHelper::getStoreData();
}

void MenuStoreLayer::storeDataCallback(std::string price)
{
	//hide the loading...image
	//create and display a string with the price
	//display purchase button
}

void MenuStoreLayer::createLoadingLabel()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	/*
	The score value must be set incorrectly at first.  See createLevelLabel() for an explanation.  This should be fixed.
	*/
    CCLabelTTF * _highScoreLabel = CCLabelTTF::create("Loading...", "Verdana-Bold", 60.0); 
    _highScoreLabel->setColor(ccc3(255,255,255));
	Size originalSize = _highScoreLabel->getContentSize();
	float laneHeight = (winSize.height / 19.0) / 2; //this /2 is so I can fit two labels in one lane
	float laneMargin = laneHeight * .05;
	float desiredLabelHeight = laneHeight - (laneMargin + laneMargin);
	float scaleRatio = desiredLabelHeight / originalSize.height;
	_highScoreLabel->setScale(scaleRatio);
	_highScoreLabel->setContentSize(CCSize(originalSize.width * scaleRatio, originalSize.height * scaleRatio));

	//_highScoreLabel->setAnchorPoint(ccp(1,1));
	//_highScoreLabel->setPosition(ccp(winSize.width - laneMargin, winSize.height - laneMargin));
	_highScoreLabel->setAnchorPoint(ccp(1,0));
	_highScoreLabel->setPosition(ccp(winSize.width - laneMargin, laneHeight + laneMargin));
    this->addChild(_highScoreLabel);
}

#include "MenuStoreLayer.h"
#include "PurchaseHelper.h"

using namespace cocos2d;

bool MenuStoreLayer::init()
{
	bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

		this->createLoadingLabel();

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

CCMenuItemImage* MenuStoreLayer::createPurchaseButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 670;
	float originalHeight = 144;

	CCMenuItemImage *purchaseImage = CCMenuItemImage::create(
		"purchase_ad_removal_orange.png",	//TODO: change this image!
		"purchase_ad_removal_yellow.png",
		this,
		menu_selector(MenuStoreLayer::makePurchase));

	float scaleRatio = (windowSize.width *.6) / purchaseImage->getContentSize().width;
	purchaseImage->setScale(scaleRatio);
	purchaseImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .1));

	return purchaseImage;
}

void MenuStoreLayer::makePurchase(CCObject* pSender)
{
	PurchaseHelper::makePurchase();
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

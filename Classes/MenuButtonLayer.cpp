#include "MenuButtonLayer.h"
#include "GameLayer.h"
#include "LevelSelectLayer.h"
#include "MainModeLayer.h"
#include "SimpleAudioEngine.h"
#include "2d/CCClippingNode.h"
#include "PurchaseHelper.h"

using namespace cocos2d;
 
bool MenuButtonLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

		//add title image
		float originalWidth = 576;
		float originalHeight = 144;
		_titleImage = CCSprite::create("egg_scramble_title.png", CCRectMake(0, 0, originalWidth, originalHeight));
        
		float scaleRatio = (windowSize.width *.7) / _titleImage->getContentSize().width;
		_titleImage->setScale(scaleRatio);
		_titleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
		this->addChild(_titleImage);

		//create main menu
		CCMenuItemImage* startGameImage = this->createStartGameButton();
		CCMenuItemImage* eggScrambleImage = this->createEggScrambleButton();
		CCMenuItemImage* instructionsImage = this->createInstructionsButton();
		CCMenuItemImage* aboutImage = this->createAboutButton();
		CCMenuItemImage* purchaseImage = this->createPurchaseButton();

		_mainMenu = CCMenu::create(startGameImage, eggScrambleImage, instructionsImage, aboutImage, purchaseImage, NULL);
		_mainMenu->setPosition(CCPointZero);
		this->addChild(_mainMenu);

		_menuInstructionsLayer = MenuInstructionsLayer::create();
		_menuInstructionsLayer->setVisible(false);
		this->addChild(_menuInstructionsLayer);

		_menuStoreLayer = MenuStoreLayer::create();
		_menuStoreLayer->setVisible(false);
		this->addChild(_menuStoreLayer);

		_menuAboutLayer = MenuAboutLayer::create();
		_menuAboutLayer->setVisible(false);
		this->addChild(_menuAboutLayer);

		bRet = true;
    } while (0);

    return bRet;
}

void MenuButtonLayer::resetDisplay()
{
	//hide all child layers
	_menuAboutLayer->setVisible(false);
	_menuInstructionsLayer->setVisible(false);

	//display this layer's stuff
	_mainMenu->setVisible(true);
	_titleImage->setVisible(true);
}

void MenuButtonLayer::startGameCallback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(MainModeLayer::scene());
}

void MenuButtonLayer::eggScrambleCallback(CCObject* pSender)
{
	_mainMenu->setVisible(false);
	_titleImage->setVisible(false);

	LevelSelectLayer* levelSelectLayer = LevelSelectLayer::create();
	this->addChild(levelSelectLayer);
}

void MenuButtonLayer::purchaseCallback(CCObject* pSender)
{
	_mainMenu->setVisible(false);
	_titleImage->setVisible(false);

	_menuStoreLayer->setVisible(true);
}

void MenuButtonLayer::aboutCallback(CCObject* pSender)
{
	_mainMenu->setVisible(false);
	_titleImage->setVisible(false);

	_menuAboutLayer->setVisible(true);
	_menuAboutLayer->animateCredits();
}

void MenuButtonLayer::instructionsCallback(CCObject* pSender)
{
	_mainMenu->setVisible(false);
	_titleImage->setVisible(false);

	_menuInstructionsLayer->setVisible(true);
}

CCMenuItemImage* MenuButtonLayer::createInstructionsButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 576;
	float originalHeight = 144;

	CCMenuItemImage *startGameImage = CCMenuItemImage::create(
		"instructions_orange.png",
		"instructions_yellow.png",
		this,
		menu_selector(MenuButtonLayer::instructionsCallback));

	float scaleRatio = (windowSize.width *.5) / startGameImage->getContentSize().width;
	startGameImage->setScale(scaleRatio);
	startGameImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .3));

	return startGameImage;
}

CCMenuItemImage* MenuButtonLayer::createStartGameButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 576;
	float originalHeight = 144;

	CCMenuItemImage *startGameImage = CCMenuItemImage::create(
		"start_game_orange.png",
		"start_game_yellow.png",
		this,
		menu_selector(MenuButtonLayer::startGameCallback));

	float scaleRatio = (windowSize.width *.5) / startGameImage->getContentSize().width;
	startGameImage->setScale(scaleRatio);
	startGameImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .5));

	return startGameImage;
}

CCMenuItemImage* MenuButtonLayer::createEggScrambleButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 576;
	float originalHeight = 144;

	CCMenuItemImage *eggScrambleImage = CCMenuItemImage::create(
		"survival_orange.png",
		"survival_yellow.png",
		this,
		menu_selector(MenuButtonLayer::eggScrambleCallback));

	float scaleRatio = (windowSize.width *.5) / eggScrambleImage->getContentSize().width;
	eggScrambleImage->setScale(scaleRatio);
	eggScrambleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .4));

	return eggScrambleImage;
}

CCMenuItemImage* MenuButtonLayer::createAboutButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 576;
	float originalHeight = 144;

	CCMenuItemImage *aboutImage = CCMenuItemImage::create(
		"about_orange.png",
		"about_yellow.png",
		this,
		menu_selector(MenuButtonLayer::aboutCallback));

	float scaleRatio = (windowSize.width *.5) / aboutImage->getContentSize().width;
	aboutImage->setScale(scaleRatio);
	aboutImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .2));

	return aboutImage;
}

CCMenuItemImage* MenuButtonLayer::createPurchaseButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 670;
	float originalHeight = 144;

	CCMenuItemImage *purchaseImage = CCMenuItemImage::create(
		"purchase_ad_removal_orange.png",	//TODO: change this image!
		"purchase_ad_removal_yellow.png",
		this,
		menu_selector(MenuButtonLayer::purchaseCallback));

	float scaleRatio = (windowSize.width *.6) / purchaseImage->getContentSize().width;
	purchaseImage->setScale(scaleRatio);
	purchaseImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .1));

	return purchaseImage;
}
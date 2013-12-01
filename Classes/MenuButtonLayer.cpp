#include "MenuButtonLayer.h"
#include "GameLayer.h"
#include "AboutLayer.h"
 
using namespace cocos2d;
 
bool MenuButtonLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		//add title image
		float originalWidth = 576;
		float originalHeight = 144;
		CCSprite * titleImage = CCSprite::create("chicken_crossing_title.png", CCRectMake(0, 0, originalWidth, originalHeight));
		titleImage->setScale(.7);
		titleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
		this->addChild(titleImage);

		//these createButton calls should return a boolean.  If it is false, call CC_BREAK_IF(! bool)
		this->createStartGameButton();
		this->createEggScrambleButton();
		this->createAboutButton();

        bRet = true;
    } while (0);

    return bRet;
}

void MenuButtonLayer::startGameCallback(CCObject* pSender)
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(GameLayer::scene());
}

void MenuButtonLayer::eggScrambleCallback(CCObject* pSender)
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(GameLayer::scene());
}

void MenuButtonLayer::aboutCallback(CCObject* pSender)
{
	AboutLayer* _aboutLayer = new AboutLayer();
	_aboutLayer->init();
	this->addChild(_aboutLayer, 2);
}

void MenuButtonLayer::closeCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
	
}

void MenuButtonLayer::createStartGameButton()
{
	CCMenuItemImage *startGameImage = CCMenuItemImage::create(
		"start_game_orange.png",
		"start_game_yellow.png",
		this,
		menu_selector(MenuButtonLayer::startGameCallback));

	startGameImage->setScale(.5);
	// Place the menu item bottom-right conner.
	startGameImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .5));

	// Create a menu with the "close" menu item, it's an auto release object.
	CCMenu* pMenu = CCMenu::create(startGameImage, NULL);
	pMenu->setPosition(CCPointZero);

	// Add the menu to HelloWorld layer as a child layer.
	this->addChild(pMenu);
}

void MenuButtonLayer::createEggScrambleButton()
{
	CCMenuItemImage *startGameImage = CCMenuItemImage::create(
		"egg_scramble_orange.png",
		"egg_scramble_yellow.png",
		this,
		menu_selector(MenuButtonLayer::eggScrambleCallback));

	startGameImage->setScale(.5);
	// Place the menu item bottom-right conner.
	startGameImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .4));

	// Create a menu with the "close" menu item, it's an auto release object.
	CCMenu* pMenu = CCMenu::create(startGameImage, NULL);
	pMenu->setPosition(CCPointZero);

	// Add the menu to HelloWorld layer as a child layer.
	this->addChild(pMenu);
}

void MenuButtonLayer::createAboutButton()
{
	CCMenuItemImage *startGameImage = CCMenuItemImage::create(
		"about_orange.png",
		"about_yellow.png",
		this,
		menu_selector(MenuButtonLayer::aboutCallback));

	startGameImage->setScale(.5);
	// Place the menu item bottom-right conner.
	startGameImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .3));

	// Create a menu with the "close" menu item, it's an auto release object.
	CCMenu* pMenu = CCMenu::create(startGameImage, NULL);
	pMenu->setPosition(CCPointZero);

	// Add the menu to HelloWorld layer as a child layer.
	this->addChild(pMenu);
}
#include "MenuButtonLayer.h"
#include "GameLayer.h"
#include "LevelSelectLayer.h"
#include "MainModeLayer.h"

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
		CCSprite * titleImage = CCSprite::create("chicken_crossing_title.png", CCRectMake(0, 0, originalWidth, originalHeight));
		float scaleRatio = (windowSize.width *.7) / titleImage->getContentSize().width;
		titleImage->setScale(scaleRatio);
		titleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
		this->addChild(titleImage);

		//create main menu
		//these createButton calls should return a boolean.  If it is false, call CC_BREAK_IF(! bool)
		CCMenuItemImage* startGameImage = this->createStartGameButton();
		CCMenuItemImage* eggScrambleImage = this->createEggScrambleButton();
		CCMenuItemImage* aboutImage = this->createAboutButton();
		_mainMenu = CCMenu::create(startGameImage, eggScrambleImage, aboutImage, NULL);
		_mainMenu->setPosition(CCPointZero);
		this->addChild(_mainMenu);




		//create about menu
		CCMenuItemImage* closeAboutImage = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(MenuButtonLayer::closeCallback));

		closeAboutImage->setScale(.5);
		// Place the menu item bottom-right conner.
		closeAboutImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .4));

		// Create a menu with the "close" menu item, it's an auto release object.
		_aboutMenu = CCMenu::create(closeAboutImage, NULL);
		_aboutMenu->setPosition(CCPointZero);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(_aboutMenu);
		_aboutMenu->setVisible(false);

		bRet = true;
    } while (0);

    return bRet;
}

void MenuButtonLayer::startGameCallback(CCObject* pSender)
{
	//GameMode * gameMode = new MainMode();

	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(MainModeLayer::scene());
}

void MenuButtonLayer::eggScrambleCallback(CCObject* pSender)
{
	//CCDirector *pDirector = CCDirector::sharedDirector();
	//pDirector->replaceScene(GameLayer::scene());
	_mainMenu->setVisible(false);
	//_levelSelectMenu->setVisible(true);

	LevelSelectLayer* levelSelectLayer = new LevelSelectLayer();
	levelSelectLayer->init();
	this->addChild(levelSelectLayer);
}

void MenuButtonLayer::aboutCallback(CCObject* pSender)
{
	_mainMenu->setVisible(false);
	_aboutMenu->setVisible(true);

}

void MenuButtonLayer::closeCallback(CCObject* pSender)
{
	_aboutMenu->setVisible(false);
	_mainMenu->setVisible(true);	
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
		"egg_scramble_orange.png",
		"egg_scramble_yellow.png",
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
	aboutImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .3));

	return aboutImage;
}
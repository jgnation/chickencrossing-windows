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
		//TODO: add image for jgnation.com, url, credit to artists, etc.
		CCMenuItemImage* logoImage = this->createJGNationLogo();
		CCMenuItemImage* arrowImage = this->createAboutExitButton();

		cocos2d::CCMenuItemFont* pCloseItem = cocos2d::CCMenuItemFont::create(
                                            "Close",
                                            this,
                                            NULL);
		pCloseItem->setFontSize(35);
		pCloseItem->setFontName("Helvetica");
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2));


		// Create a menu with the "close" menu item, it's an auto release object.
		_aboutMenu = CCMenu::create(pCloseItem, logoImage, arrowImage, NULL);
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

CCMenuItemImage* MenuButtonLayer::createAboutExitButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidthArrow = 300;
	float originalHeightArrow = 228;
	CCMenuItemImage* arrow = CCMenuItemImage::create(
		"arrow.png",
		"arrow.png",
		this,
		menu_selector(MenuButtonLayer::closeCallback));

	float scaleRatioArrowX = (windowSize.width *.2) / arrow->getContentSize().width;
	float scaleRatioArrowY = (windowSize.height *.15) / arrow->getContentSize().height;
	arrow->setScale(scaleRatioArrowX);
	arrow->setScale(scaleRatioArrowY);
	arrow->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .20));

	return arrow;
}

CCMenuItemImage* MenuButtonLayer::createJGNationLogo()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidthLogo = 618;
	float originalHeightLogo = 517;
	CCMenuItemImage* logo = CCMenuItemImage::create(
		"jgnation_logo_med.png",
		"jgnation_logo_med.png",
		this, 
		NULL
	);

	logo->setScale((windowSize.width *.2) / logo->getContentSize().width);
	logo->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 5, CCDirector::sharedDirector()->getWinSize().height * .45));

	return logo;
}
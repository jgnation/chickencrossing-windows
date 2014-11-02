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
		_titleImage = CCSprite::create("chicken_crossing_title.png", CCRectMake(0, 0, originalWidth, originalHeight));
		float scaleRatio = (windowSize.width *.7) / _titleImage->getContentSize().width;
		_titleImage->setScale(scaleRatio);
		_titleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
		this->addChild(_titleImage);

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
		_chickenCrossingAboutImage = CCSprite::create("chicken_crossing_title.png", CCRectMake(0, 0, originalWidth, originalHeight));
		float ratio = (windowSize.width *.4) / _titleImage->getContentSize().width;
		_chickenCrossingAboutImage->setScale(ratio);
		_chickenCrossingAboutImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .9));

		_backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), windowSize.width * .5, windowSize.height * .45);
		_backgroundColor->setOpacity(100);
		_backgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
		_backgroundColor->setAnchorPoint(ccp(0,1));
		_backgroundColor->setPosition(ccp(windowSize.width * .4, windowSize.height * .8));
		
		std::string info = "Developed by JGNation\n";
		info += "www.jgnation.com\n\n";
		info += "Chicken image by bloodsong - openclipart.org\n";
		info += "Vehicle images by spadassin - openclipart.org\n";
		info += "Wood plank image by Nemo - pixabay.com\n";
		info += "All other images created by JGNation.";

		CCLabelBMFont * aboutInfo = CCLabelBMFont::create(info.c_str(), "futura-48.fnt");
		Size originalSize = aboutInfo->getContentSize();
		Size backgroundColorSize = _backgroundColor->getContentSize();
		float r = (backgroundColorSize.height / 2.0) / originalSize.height;
		aboutInfo->setScale(r);
		aboutInfo->setContentSize(CCSize(originalSize.width * r, originalSize.height * r));
		aboutInfo->setAnchorPoint(ccp(0,1));
		aboutInfo->setPosition(ccp(0 + 10, backgroundColorSize.height - 10));
		_backgroundColor->addChild(aboutInfo);

		_logoImage = this->createJGNationLogo();
		_aboutExitImage = this->createAboutExitButton();
		CCMenu* pMenu = CCMenu::create(_aboutExitImage, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(_logoImage);
		this->addChild(_chickenCrossingAboutImage);
		this->addChild(pMenu);
		this->addChild(_backgroundColor);


		//Hide the about screen stuff
		_logoImage->setVisible(false);
		_aboutExitImage->setVisible(false);
		_chickenCrossingAboutImage->setVisible(false);
		_backgroundColor->setVisible(false);

		bRet = true;
    } while (0);

    return bRet;
}

void MenuButtonLayer::startGameCallback(CCObject* pSender)
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(MainModeLayer::scene());
}

void MenuButtonLayer::eggScrambleCallback(CCObject* pSender)
{
	_mainMenu->setVisible(false);
	_titleImage->setVisible(false);

	LevelSelectLayer* levelSelectLayer = new LevelSelectLayer();
	levelSelectLayer->init();
	this->addChild(levelSelectLayer);
}

void MenuButtonLayer::aboutCallback(CCObject* pSender)
{
	_mainMenu->setVisible(false);
	_titleImage->setVisible(false);

	_logoImage->setVisible(true);
	_aboutExitImage->setVisible(true);
	_chickenCrossingAboutImage->setVisible(true);
	_backgroundColor->setVisible(true);
}

void MenuButtonLayer::aboutExitCallback(CCObject* pSender)
{
	_aboutExitImage->setVisible(false);
	_chickenCrossingAboutImage->setVisible(false);
	_logoImage->setVisible(false);
	_backgroundColor->setVisible(false);

	_mainMenu->setVisible(true);
	_titleImage->setVisible(true);
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
		menu_selector(MenuButtonLayer::aboutExitCallback));

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
	logo->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 5, CCDirector::sharedDirector()->getWinSize().height * .55));

	return logo;
}
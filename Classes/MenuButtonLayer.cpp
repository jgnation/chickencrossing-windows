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
		_titleImage = CCSprite::create("egg_scramble_title.png", CCRectMake(0, 0, originalWidth, originalHeight));
        
		float scaleRatio = (windowSize.width *.7) / _titleImage->getContentSize().width;
		_titleImage->setScale(scaleRatio);
		_titleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
		this->addChild(_titleImage);

		//create main menu
		//these createButton calls should return a boolean.  If it is false, call CC_BREAK_IF(! bool)
		CCMenuItemImage* startGameImage = this->createStartGameButton();
		CCMenuItemImage* eggScrambleImage = this->createEggScrambleButton();
		CCMenuItemImage* instructionsImage = this->createInstructionsButton();
		CCMenuItemImage* aboutImage = this->createAboutButton();
		_mainMenu = CCMenu::create(startGameImage, eggScrambleImage, instructionsImage, aboutImage, NULL);
		_mainMenu->setPosition(CCPointZero);
		this->addChild(_mainMenu);

		//create about screen
		this->createAboutScreen();

		//create instructions screen
		this->createInstructionScreen();

		bRet = true;
    } while (0);

    return bRet;
}

void MenuButtonLayer::createInstructionScreen()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 576;
	float originalHeight = 144;

	_chickenCrossingInstructionsImage = CCSprite::create("egg_scramble_title.png", CCRectMake(0, 0, originalWidth, originalHeight));
	float ratio = (windowSize.width *.4) / _chickenCrossingInstructionsImage->getContentSize().width;
	_chickenCrossingInstructionsImage->setScale(ratio);
	_chickenCrossingInstructionsImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .9));

	_instructionsBackgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), windowSize.width * .8, windowSize.height * .5);
	_instructionsBackgroundColor->setOpacity(200);
	_instructionsBackgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
	_instructionsBackgroundColor->setAnchorPoint(ccp(0,1));
	_instructionsBackgroundColor->setPosition(ccp(windowSize.width * .1, windowSize.height * .8));

	std::string info = "Swipe the screen in the direction you want to move.\n";
	info += "\n";
	info += "Main mode:\n";
	info += "Collect the eggs to progress through the levels.\n";
	info += "Each level requires you to collect one more egg than the last.\n";
	info += "\n";
	info += "Survival mode:\n";
	info += "Collect as many eggs as possible.\n";
	info += "Watch out for accelerating traffic!\n";
	info += "Traffic will accelerate as your score increases.";

	CCLabelBMFont * aboutInfo = CCLabelBMFont::create(info.c_str(), "futura-48.fnt");
	Size originalSize = aboutInfo->getContentSize();
	Size backgroundColorSize = _instructionsBackgroundColor->getContentSize();
	float ry = (backgroundColorSize.height * .6) / originalSize.height;
	float rx = (backgroundColorSize.width * .9) / originalSize.width;
	aboutInfo->setScaleY(ry);
	aboutInfo->setScaleX(rx);
	aboutInfo->setContentSize(CCSize(originalSize.width * rx, originalSize.height * ry));
	aboutInfo->setAnchorPoint(ccp(0,1));
	aboutInfo->setPosition(ccp(0 + 10, backgroundColorSize.height - 10));
	aboutInfo->setColor(ccc3(40, 40, 40));
	_instructionsBackgroundColor->addChild(aboutInfo);

	_instructionsExitImage = this->createInstructionsExitButton();
	CCMenu* pMenu = CCMenu::create(_instructionsExitImage, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(_chickenCrossingInstructionsImage);
	this->addChild(pMenu);
	this->addChild(_instructionsBackgroundColor);

	//Hide the about screen stuff
	_instructionsExitImage->setVisible(false);
	_chickenCrossingInstructionsImage->setVisible(false);
	_instructionsBackgroundColor->setVisible(false);
}

void MenuButtonLayer::createAboutScreen()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	_backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), windowSize.width * .8, windowSize.height * .4);
	_backgroundColor->setOpacity(200);
	_backgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
	_backgroundColor->setAnchorPoint(ccp(0,1));
	_backgroundColor->setPosition(ccp(windowSize.width * .1, windowSize.height * .7));
		
	std::string info = "Developed by JGNation\n";
	info += "www.jgnation.com\n\n";
	info += "Chicken image by bloodsong\n";
	info += "openclipart.org\n\n";
	info += "Vehicle images by spadassin\n";
	info += "openclipart.org\n\n";
	info += "Wood plank image by Nemo\n";
	info += "pixabay.com\n\n";
	info += "All other images created by JGNation.";

	CCLabelBMFont * aboutInfo = CCLabelBMFont::create(info.c_str(), "futura-48.fnt");
	Size originalSize = aboutInfo->getContentSize();
	Size backgroundColorSize = _backgroundColor->getContentSize();
	float ry = (backgroundColorSize.height * .8) / originalSize.height;
	float rx = (backgroundColorSize.width * .6) / originalSize.width;
	aboutInfo->setScaleY(ry);
	aboutInfo->setScaleX(rx);
	aboutInfo->setContentSize(CCSize(originalSize.width * rx, originalSize.height * ry));
	aboutInfo->setAnchorPoint(ccp(0,1));
	aboutInfo->setPosition(ccp(0 + 10, backgroundColorSize.height - 10));
	//aboutInfo->setColor(ccc3(240, 40, 40));
	aboutInfo->setColor(ccc3(40, 40, 40));
	_backgroundColor->addChild(aboutInfo);

	_logoImage = this->createJGNationLogo();
	_aboutExitImage = this->createAboutExitButton();
	CCMenu* pMenu = CCMenu::create(_aboutExitImage, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(_logoImage);
	this->addChild(pMenu);
	this->addChild(_backgroundColor);


	//Hide the about screen stuff
	_logoImage->setVisible(false);
	_aboutExitImage->setVisible(false);
	_backgroundColor->setVisible(false);
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
	_backgroundColor->setVisible(true);
}

void MenuButtonLayer::instructionsCallback(CCObject* pSender)
{
	_mainMenu->setVisible(false);
	_titleImage->setVisible(false);

	_instructionsBackgroundColor->setVisible(true);
	_chickenCrossingInstructionsImage->setVisible(true);
	_instructionsExitImage->setVisible(true);
}

void MenuButtonLayer::aboutExitCallback(CCObject* pSender)
{
	_aboutExitImage->setVisible(false);
	_logoImage->setVisible(false);
	_backgroundColor->setVisible(false);

	_mainMenu->setVisible(true);
	_titleImage->setVisible(true);
}

void MenuButtonLayer::instructionsExitCallback(CCObject* pSender)
{
	_instructionsBackgroundColor->setVisible(false);
	_chickenCrossingInstructionsImage->setVisible(false);
	_instructionsExitImage->setVisible(false);

	_mainMenu->setVisible(true);
	_titleImage->setVisible(true);
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

CCMenuItemImage* MenuButtonLayer::createInstructionsExitButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidthArrow = 300;
	float originalHeightArrow = 228;
	CCMenuItemImage* arrow = CCMenuItemImage::create(
		"arrow.png",
		"arrow.png",
		this,
		menu_selector(MenuButtonLayer::instructionsExitCallback));

	float scaleRatioArrowX = (windowSize.width *.2) / arrow->getContentSize().width;
	float scaleRatioArrowY = (windowSize.height *.15) / arrow->getContentSize().height;
	arrow->setScale(scaleRatioArrowX);
	arrow->setScale(scaleRatioArrowY);
	arrow->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .20));

	return arrow;
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

	logo->setScale((windowSize.height * .2) / logo->getContentSize().height);
	logo->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .85));

	return logo;
}
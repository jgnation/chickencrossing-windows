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
		//these createButton calls should return a boolean.  If it is false, call CC_BREAK_IF(! bool)
		CCMenuItemImage* startGameImage = this->createStartGameButton();
		CCMenuItemImage* eggScrambleImage = this->createEggScrambleButton();
		CCMenuItemImage* instructionsImage = this->createInstructionsButton();
		CCMenuItemImage* aboutImage = this->createAboutButton();
		CCMenuItemImage* purchaseImage = this->createPurchaseButton();
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
	_chickenCrossingInstructionsImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .85));

	_instructionsBackgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), windowSize.width * .8, windowSize.height * .5);
	_instructionsBackgroundColor->setOpacity(200);
	_instructionsBackgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
	_instructionsBackgroundColor->setAnchorPoint(ccp(0,1));
	_instructionsBackgroundColor->setPosition(ccp(windowSize.width * .1, windowSize.height * .8));

	std::string info = "Swipe the screen in the direction you want to move.\n";
	info += "\n";
	info += "Main mode:\n";
	info += "Collect the eggs to progress through the levels.\n";
	info += "Each level requires you to collect one more egg\n";
	info += "than the last.\n";
	info += "\n";
	info += "Survival mode:\n";
	info += "Collect as many eggs as possible.\n";
	info += "Watch out for accelerating traffic!\n";
	info += "Traffic will accelerate as your score increases.";

	CCLabelBMFont * aboutInfo = CCLabelBMFont::create(info.c_str(), "futura-48.fnt");
	aboutInfo->setAnchorPoint(ccp(0,1));
	Size originalSize = aboutInfo->getContentSize();
	Size backgroundColorSize = _instructionsBackgroundColor->getContentSize();
	float ry = (backgroundColorSize.height * .6) / originalSize.height;
	float rx = (backgroundColorSize.width * .9) / originalSize.width;
	aboutInfo->setScaleY(ry);
	aboutInfo->setScaleX(rx);
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

	_logoImage = this->createJGNationLogo();
	_aboutExitImage = this->createAboutExitButton();
	CCMenu* pMenu = CCMenu::create(_aboutExitImage, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(_logoImage);
	this->addChild(pMenu);
	this->addChild(_backgroundColor);

	this->createAboutScreenInfo();

	//Hide the about screen stuff
	_logoImage->setVisible(false);
	_aboutExitImage->setVisible(false);
	_backgroundColor->setVisible(false);
}

void MenuButtonLayer::createAboutScreenInfo()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	CCDrawNode * stencil = CCDrawNode::create();
	CCPoint rectangle[4];
    rectangle[0] = ccp(windowSize.width * .1, windowSize.height * .3); //bottom left
    rectangle[1] = ccp(windowSize.width * .9, windowSize.height * .3); //bottom right
    rectangle[2] = ccp(windowSize.width * .9, windowSize.height * .7); //top right
	rectangle[3] = ccp(windowSize.width * .1, windowSize.height * .7); //top left
	ccColor4F white(255, 255, 255, 255);
	ccColor4F black(1, 1, 1, 1);
	stencil->drawPolygon(rectangle, 4, white, 1, black);

	CCClippingNode* clippingNode = CCClippingNode::create(stencil);

	std::string info = "Version 1.0\n\n";
	info += "Developed by JGNation\n";
	info += "www.jgnation.com\n\n";
	info += "Chicken image by bloodsong\n";
	info += "openclipart.org\n\n";
	info += "Vehicle images by spadassin\n";
	info += "openclipart.org\n\n";
	info += "Wood plank image by Nemo\n";
	info += "pixabay.com\n\n";
	info += "Skull image by OpenClips\n";
	info += "pixabay.com\n\n";
	info += "All other images created by JGNation.\n\n";
	info += "Music by Roald Strauss\n";
	info += "IndieGameMusic.com";
	_aboutInfo = CCLabelBMFont::create(info.c_str(), "futura-48.fnt");
	Size originalSize = _aboutInfo->getContentSize();
	float scale = (windowSize.width * .8) / originalSize.width;
	_aboutInfo->setAnchorPoint(ccp(0,1));
	_aboutInfo->setPosition(ccp(windowSize.width * .1, windowSize.height * .3)); //set below bottom left corner
	_aboutInfo->setScale(scale);
	_aboutInfo->setColor(ccc3(40, 40, 40));
	clippingNode->addChild(_aboutInfo);
	this->addChild(clippingNode);
	_aboutInfo->setVisible(false);
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
	PurchaseHelper::makePurchase();
}

void MenuButtonLayer::aboutCallback(CCObject* pSender)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	_aboutInfo->setPosition(ccp(windowSize.width * .1, windowSize.height * .3)); //set below bottom left corner

	Size originalSize = _aboutInfo->getContentSize();
	float scale = (windowSize.width * .8) / originalSize.width;
	float scaledHeight = originalSize.height * scale;
	float targetHeight = (windowSize.height * .7) + scaledHeight;

	CCFiniteTimeAction * actionMove1 = CCMoveTo::create(10.0, ccp(windowSize.width * .1, targetHeight));
	CCFiniteTimeAction * actionMove2 = CCMoveTo::create(0.0, ccp(windowSize.width * .1, windowSize.height * .3));
	CCFiniteTimeAction * actionMove3 = CCMoveTo::create(0.5, ccp(windowSize.width * .1, windowSize.height * .3)); //pause in this position
	Vector<FiniteTimeAction *> allActions;
	allActions.pushBack(actionMove1);
	allActions.pushBack(actionMove2);
	allActions.pushBack(actionMove3);
	CCSequence* pulseSequence = CCSequence::create(allActions);
	CCRepeatForever* repeat = CCRepeatForever::create(pulseSequence);
	_aboutInfo->setVisible(true);
	_aboutInfo->runAction(repeat);

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
	_aboutInfo->stopAllActions();
	_aboutInfo->setVisible(false);

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

CCMenuItemImage* MenuButtonLayer::createPurchaseButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 576;
	float originalHeight = 144;

	CCMenuItemImage *purchaseImage = CCMenuItemImage::create(
		"about_orange.png",	//TODO: change this image!
		"about_yellow.png",
		this,
		menu_selector(MenuButtonLayer::purchaseCallback));

	float scaleRatio = (windowSize.width *.5) / purchaseImage->getContentSize().width;
	purchaseImage->setScale(scaleRatio);
	purchaseImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .1));

	return purchaseImage;
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

	logo->setScale((windowSize.height * .15) / logo->getContentSize().height);
	logo->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .80));

	return logo;
}
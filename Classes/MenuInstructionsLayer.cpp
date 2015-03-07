#include "MenuInstructionsLayer.h"
#include "MenuButtonLayer.h"

using namespace cocos2d;

bool MenuInstructionsLayer::init()
{
	bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		this->createInstructionScreen();

		bRet = true;
    } while (0);

    return bRet;
}

void MenuInstructionsLayer::createInstructionScreen()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidth = 576;
	float originalHeight = 144;

	Sprite * _chickenCrossingInstructionsImage = Sprite::create("egg_scramble_title.png", CCRectMake(0, 0, originalWidth, originalHeight));
	float ratio = (windowSize.width *.4) / _chickenCrossingInstructionsImage->getContentSize().width;
	_chickenCrossingInstructionsImage->setScale(ratio);
	_chickenCrossingInstructionsImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .85));

	CCLayerColor * _instructionsBackgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), windowSize.width * .8, windowSize.height * .5);
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

	CCMenuItemImage * _instructionsExitImage = this->createInstructionsExitButton();
	CCMenu* pMenu = CCMenu::create(_instructionsExitImage, NULL);
	pMenu->setPosition(ccp(0,0));
	this->addChild(_chickenCrossingInstructionsImage);
	this->addChild(pMenu);
	this->addChild(_instructionsBackgroundColor);
}

CCMenuItemImage* MenuInstructionsLayer::createInstructionsExitButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidthArrow = 300;
	float originalHeightArrow = 228;
	CCMenuItemImage* arrow = CCMenuItemImage::create(
		"arrow_left.png",
		"arrow_left.png",
		this,
		menu_selector(MenuInstructionsLayer::instructionsExitCallback));

	float scaleRatioArrowX = (windowSize.width *.2) / arrow->getContentSize().width;
	float scaleRatioArrowY = (windowSize.height *.15) / arrow->getContentSize().height;
	arrow->setScale(scaleRatioArrowX);
	arrow->setScale(scaleRatioArrowY);
	arrow->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .20));

	return arrow;
}

void MenuInstructionsLayer::instructionsExitCallback(CCObject* pSender)
{
	Node * parent = this->getParent();
	MenuButtonLayer* menuButtonLayer = dynamic_cast<MenuButtonLayer*>(parent);
	if(menuButtonLayer != 0)
	{
		menuButtonLayer->resetDisplay();
	}
}

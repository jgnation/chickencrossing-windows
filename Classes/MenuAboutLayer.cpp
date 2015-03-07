#include "MenuAboutLayer.h"
#include "MenuButtonLayer.h"

using namespace cocos2d;

bool MenuAboutLayer::init()
{
	bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		this->createAboutScreen();

		bRet = true;
    } while (0);

    return bRet;
}

void MenuAboutLayer::createAboutScreen()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	CCLayerColor * _backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), windowSize.width * .8, windowSize.height * .4);
	_backgroundColor->setOpacity(200);
	_backgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
	_backgroundColor->setAnchorPoint(ccp(0,1));
	_backgroundColor->setPosition(ccp(windowSize.width * .1, windowSize.height * .7));

	CCMenuItemImage * _logoImage = this->createJGNationLogo();
	CCMenuItemImage * _aboutExitImage = this->createAboutExitButton();
	CCMenu* pMenu = CCMenu::create(_aboutExitImage, NULL);
	pMenu->setPosition(ccp(0,0));
	this->addChild(_logoImage);
	this->addChild(pMenu);
	this->addChild(_backgroundColor);

	this->createAboutScreenInfo();

	//Hide the about screen stuff
	//_logoImage->setVisible(false);
	//_aboutExitImage->setVisible(false);
	//_backgroundColor->setVisible(false);
}

void MenuAboutLayer::createAboutScreenInfo()
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

	std::string info = "Version 1.0.3\n\n";
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
	//_aboutInfo->setVisible(false);
}

CCMenuItemImage* MenuAboutLayer::createJGNationLogo()
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

CCMenuItemImage* MenuAboutLayer::createAboutExitButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	float originalWidthArrow = 300;
	float originalHeightArrow = 228;
	CCMenuItemImage* arrow = CCMenuItemImage::create(
		"arrow_left.png",
		"arrow_left.png",
		this,
		menu_selector(MenuAboutLayer::aboutExitCallback));

	float scaleRatioArrowX = (windowSize.width *.2) / arrow->getContentSize().width;
	float scaleRatioArrowY = (windowSize.height *.15) / arrow->getContentSize().height;
	arrow->setScale(scaleRatioArrowX);
	arrow->setScale(scaleRatioArrowY);
	arrow->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .20));

	return arrow;
}

void MenuAboutLayer::aboutExitCallback(CCObject* pSender)
{
	Node * parent = this->getParent();
	MenuButtonLayer* menuButtonLayer = dynamic_cast<MenuButtonLayer*>(parent);
	if(menuButtonLayer != 0)
	{
		menuButtonLayer->resetDisplay();
	}

	_aboutInfo->stopAllActions();
}

void MenuAboutLayer::animateCredits()
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
}

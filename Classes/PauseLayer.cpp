#include "PauseLayer.h"
#include "GameLayer.h"

using namespace cocos2d;

bool PauseLayer::init()
{
    if (CCLayer::init()) {     
        this->createResumeButton();
    }
 
    return true;
}

void PauseLayer::createResumeButton()
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	float originalWidthArrow = 400;
	float originalHeightArrow = 400;
	CCMenuItemImage* arrow1 = CCMenuItemImage::create(
		"resume.png",
		"resume.png",
		this,
		menu_selector(PauseLayer::resume));

	float scaleRatioArrowX = (windowSize.width *.2) / arrow1->getContentSize().width;
	arrow1->setScale(scaleRatioArrowX);
	arrow1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2));

	_buttonMenu = CCMenu::create(arrow1, NULL);
	_buttonMenu->setPosition(ccp(0,0));

    _buttonMenu->setVisible(false);
	this->addChild(_buttonMenu);
}

void PauseLayer::pause()
{
    _buttonMenu->setVisible(true);
}

void PauseLayer::resume(CCObject* pSender)
{
    _buttonMenu->setVisible(false);
    
    Node* parent = this->getParent();
    GameLayer* gameLayer = dynamic_cast<GameLayer*>(parent);
    gameLayer->resumeGame();
    
}


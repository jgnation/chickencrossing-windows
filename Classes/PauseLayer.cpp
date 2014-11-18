#include "PauseLayer.h"
#include "GameLayer.h"

using namespace cocos2d;

bool PauseLayer::init()
{
    if (CCLayer::init()) {     
  
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
		menu_selector(GameLayer::resumeGame));

	float scaleRatioArrowX = (windowSize.width *.2) / arrow1->getContentSize().width;
	arrow1->setScale(scaleRatioArrowX);
	arrow1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2));

	CCMenu* pMenu = CCMenu::create(arrow1, NULL);
	pMenu->setPosition(CCPointZero);

	this->addChild(pMenu);
}

void PauseLayer::resume(CCObject* pSender)
{
}

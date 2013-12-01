#include "AboutLayer.h"
 
using namespace cocos2d;
 
bool AboutLayer::init()
{
    if (CCLayer::init()) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
 
        CCMenuItemImage *startGameImage = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(AboutLayer::closeButtonCallback));

		startGameImage->setScale(.5);
		// Place the menu item bottom-right conner.
		startGameImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .4));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(startGameImage, NULL);
		pMenu->setPosition(CCPointZero);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu);

    }
 
    return true;
}
 
void AboutLayer::closeButtonCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}

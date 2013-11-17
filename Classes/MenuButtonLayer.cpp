#include "MenuButtonLayer.h"
#include "GameLayer.h"
 
using namespace cocos2d;
 
bool MenuButtonLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		// Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(MenuButtonLayer::menuStartGameCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 300, 300));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu);
        bRet = true;
    } while (0);

    return bRet;
}

void MenuButtonLayer::menuStartGameCallback(CCObject* pSender)
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(GameLayer::scene());
}

void MenuButtonLayer::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}
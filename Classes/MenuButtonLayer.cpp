#include "MenuButtonLayer.h"
#include "GameLayer.h"
 
using namespace cocos2d;
 
bool MenuButtonLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		//add title image
		float originalWidth = 576;
		float originalHeight = 144;
		CCSprite * titleImage = CCSprite::create("chicken_crossing_title.png", CCRectMake(0, 0, originalWidth, originalHeight));
		titleImage->setScale(.7);
		titleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 300, 350));
		this->addChild(titleImage);

		//add buttons

		// Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "start_game_orange.png",
            "start_game_yellow.png",
            this,
            menu_selector(MenuButtonLayer::menuStartGameCallback));
        CC_BREAK_IF(! pCloseItem);

		pCloseItem->setScale(.5);
        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 300, 100));

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
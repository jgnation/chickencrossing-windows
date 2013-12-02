#include "GameOverLayer.h"
#include "MenuLayer.h"
 
using namespace cocos2d;
 
bool GameOverLayer::init()
{
    if (CCLayer::init()) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
 
        //add game over image
		float originalWidth = 576;
		float originalHeight = 144;
		CCSprite * titleImage = CCSprite::create("game_over.png", CCRectMake(0, 0, originalWidth, originalHeight));
		//titleImage->setScale(.7);
		titleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
		this->addChild(titleImage);


		CCMenuItemImage *startGameImage = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(GameOverLayer::closeButtonCallback));

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

void GameOverLayer::closeButtonCallback(CCObject* pSender)
{
	CCScene *pScene = MenuLayer::scene();
    //CCScene *s = CCTransitionSplitRows::transitionWithDuration(0.5, pScene);
    //CCDirector::sharedDirector()->replaceScene(s);

	CCDirector::sharedDirector()->replaceScene(pScene);
}
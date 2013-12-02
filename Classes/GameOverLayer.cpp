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
		titleImage = CCSprite::create("game_over.png", CCRectMake(0, 0, originalWidth, originalHeight));
		//titleImage->setScale(.7);
		titleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
		this->addChild(titleImage);


		arrow1 = CCMenuItemImage::create(
			"arrow.png",
			"arrow.png",
			this,
			menu_selector(GameOverLayer::nextButton1Callback));

		arrow1->setScale(.5);
		// Place the menu item bottom-right conner.
		arrow1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .4));

		// Create a menu with the "close" menu item, it's an auto release object.
		pMenu = CCMenu::create(arrow1, NULL);
		pMenu->setPosition(CCPointZero);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu);
    }
 
    return true;
}

void GameOverLayer::nextButton1Callback(CCObject* pSender)
{
	//remove the game over and arrow images
	titleImage->setVisible(false);
	arrow1->setVisible(false);
	pMenu->setVisible(false);

	//display scores and next button
	CCMenuItemImage *arrow2 = CCMenuItemImage::create(
			"arrow.png",
			"arrow.png",
			this,
			menu_selector(GameOverLayer::nextButton2Callback));

	arrow2->setScale(.5);
	// Place the menu item bottom-right conner.
	arrow2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .4));

	// Create a menu with the "close" menu item, it's an auto release object.
	CCMenu* pMenu = CCMenu::create(arrow2, NULL);
	pMenu->setPosition(CCPointZero);

	// Add the menu to HelloWorld layer as a child layer.
	this->addChild(pMenu);

}

void GameOverLayer::nextButton2Callback(CCObject* pSender)
{
	CCScene *pScene = MenuLayer::scene();
    //CCScene *s = CCTransitionSplitRows::transitionWithDuration(0.5, pScene);
    //CCDirector::sharedDirector()->replaceScene(s);

	CCDirector::sharedDirector()->replaceScene(pScene);
}
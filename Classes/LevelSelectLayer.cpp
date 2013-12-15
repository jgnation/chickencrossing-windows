#include "LevelSelectLayer.h"
#include "GameLayer.h"
#include "EggScrambleModeLayer.h"
 
using namespace cocos2d;
 
bool LevelSelectLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		
		CCMenuItemImage* number1Image = CCMenuItemImage::create(
			"number1.png",
			"number1.png",
			this,
			menu_selector(LevelSelectLayer::number1Callback));
		number1Image->setScale(.3);
		// Place the menu item bottom-right conner.
		number1Image->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width * .3, CCDirector::sharedDirector()->getWinSize().height * .5));

		CCMenuItemImage* number2Image = CCMenuItemImage::create(
			"number2.png",
			"number2.png",
			this,
			menu_selector(LevelSelectLayer::number2Callback));
		number2Image->setScale(.3);
		// Place the menu item bottom-right conner.
		number2Image->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width *.5, CCDirector::sharedDirector()->getWinSize().height * .5));

		CCMenuItemImage* number3Image = CCMenuItemImage::create(
			"number3.png",
			"number3.png",
			this,
			menu_selector(LevelSelectLayer::number3Callback));
		number3Image->setScale(.3);
		// Place the menu item bottom-right conner.
		number3Image->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width *.7, CCDirector::sharedDirector()->getWinSize().height * .5));

		_mainMenu = CCMenu::create(number1Image, number2Image, number3Image, NULL);
		_mainMenu->setPosition(CCPointZero);
		this->addChild(_mainMenu);

		bRet = true;
    } while (0);

    return bRet;
}

void LevelSelectLayer::number1Callback(CCObject* pSender)
{
	//GameMode * gameMode = new EggScrambleMode(1);

	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(EggScrambleModeLayer::scene(1));
}

void LevelSelectLayer::number2Callback(CCObject* pSender)
{
	//GameMode * gameMode = new EggScrambleMode(2);

	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(EggScrambleModeLayer::scene(2));
}

void LevelSelectLayer::number3Callback(CCObject* pSender)
{
	//GameMode * gameMode = new EggScrambleMode(3);

	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(EggScrambleModeLayer::scene(3));
}


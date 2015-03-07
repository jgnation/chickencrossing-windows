#include "LevelSelectLayer.h"
#include "GameLayer.h"
#include "EggScrambleModeLayer.h"
#include "SimpleAudioEngine.h"
 
using namespace cocos2d;
 
bool LevelSelectLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
		CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

		float originalWidth = 576;
		float originalHeight = 144;
		CCSprite* selectLevel = CCSprite::create("select_level.png", CCRectMake(0, 0, originalWidth, originalHeight));
		float scaleRatio = (windowSize.width *.5) / selectLevel->getContentSize().width;
		selectLevel->setScale(scaleRatio);
		selectLevel->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .8));
		this->addChild(selectLevel);

		CCMenuItemImage* number1Image = this->createLevelButton(1, ccp(CCDirector::sharedDirector()->getWinSize().width * .2, CCDirector::sharedDirector()->getWinSize().height * .6));
		CCMenuItemImage* number2Image = this->createLevelButton(2, ccp(CCDirector::sharedDirector()->getWinSize().width * .4, CCDirector::sharedDirector()->getWinSize().height * .6));
		CCMenuItemImage* number3Image = this->createLevelButton(3, ccp(CCDirector::sharedDirector()->getWinSize().width * .6, CCDirector::sharedDirector()->getWinSize().height * .6));
		CCMenuItemImage* number4Image = this->createLevelButton(4, ccp(CCDirector::sharedDirector()->getWinSize().width * .8, CCDirector::sharedDirector()->getWinSize().height * .6));

		CCMenuItemImage* number5Image = this->createLevelButton(5, ccp(CCDirector::sharedDirector()->getWinSize().width * .2, CCDirector::sharedDirector()->getWinSize().height * .4));
		CCMenuItemImage* number6Image = this->createLevelButton(6, ccp(CCDirector::sharedDirector()->getWinSize().width * .4, CCDirector::sharedDirector()->getWinSize().height * .4));
		CCMenuItemImage* number7Image = this->createLevelButton(7, ccp(CCDirector::sharedDirector()->getWinSize().width * .6, CCDirector::sharedDirector()->getWinSize().height * .4));
		CCMenuItemImage* number8Image = this->createLevelButton(8, ccp(CCDirector::sharedDirector()->getWinSize().width * .8, CCDirector::sharedDirector()->getWinSize().height * .4));

		CCMenuItemImage* number9Image = this->createLevelButton(9, ccp(CCDirector::sharedDirector()->getWinSize().width * .2, CCDirector::sharedDirector()->getWinSize().height * .2));
		CCMenuItemImage* number10Image = this->createLevelButton(10, ccp(CCDirector::sharedDirector()->getWinSize().width * .4, CCDirector::sharedDirector()->getWinSize().height * .2));
		CCMenuItemImage* number11Image = this->createLevelButton(11, ccp(CCDirector::sharedDirector()->getWinSize().width * .6, CCDirector::sharedDirector()->getWinSize().height * .2));
		CCMenuItemImage* number12Image = this->createLevelButton(12, ccp(CCDirector::sharedDirector()->getWinSize().width * .8, CCDirector::sharedDirector()->getWinSize().height * .2));

		_mainMenu = CCMenu::create(
			number1Image, 
			number2Image, 
			number3Image, 
			number4Image, 
			number5Image,
			number6Image,
			number7Image,
			number8Image,
			number9Image,
			number10Image,
			number11Image,
			number12Image,
			NULL
		);
		_mainMenu->setPosition(ccp(0,0));
		this->addChild(_mainMenu);

		bRet = true;
    } while (0);

    return bRet;
}

CCMenuItemImage* LevelSelectLayer::createLevelButton(int levelNumber, const Point &position)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	std::ostringstream os;
	os << levelNumber;
    std::string fileName = "num_" + os.str() + ".png";

	CCMenuItemImage* levelImage = CCMenuItemImage::create(
		fileName.c_str(),
		fileName.c_str(),
		this,
		menu_selector(LevelSelectLayer::levelSelectCallback));

    float scaleRatioX = (windowSize.width * .2) / levelImage->getContentSize().width;
	levelImage->setScaleX(scaleRatioX); //TODO: scale x and y independently? //This will work as long as the width is not greater than the height (they will overlap if that is the case)
	
	float scaleRatioY = (windowSize.height * .15) / levelImage->getContentSize().width;
	levelImage->setScaleY(scaleRatioY);
	
	levelImage->setTag(levelNumber);
	levelImage->setPosition(position);

	return levelImage;
}

void LevelSelectLayer::levelSelectCallback(CCObject* pSender)
{
	CCMenuItem * item = (CCMenuItem *) pSender;
	int levelNumber = item->getTag();

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(EggScrambleModeLayer::scene(levelNumber));
}

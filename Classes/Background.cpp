#include "Background.h"

using namespace cocos2d;

Background* Background::create(std::string backgroundFileName)
{
    Background *pGOL = new Background();
    if (pGOL && pGOL->init(backgroundFileName)) {
        pGOL->autorelease();
        return pGOL;
    }
    CC_SAFE_DELETE(pGOL);
    return NULL;
}

bool Background::init(std::string backgroundFileName)
{
    bool bRet = false;
    do 
    {
		//http://www.cocos2d-iphone.org/forums/topic/changing-the-aspect-fit-of-an-image-on-a-sprite-or-a-layer/
		//set up background image and scale it appropriately
		_sprite = CCSprite::create(backgroundFileName.c_str());
		_sprite->setAnchorPoint(ccp(0, 0));
		_sprite->setPosition(ccp(0, 0));
		CCSize winSize = CCDirector::sharedDirector()->getWinSize(); //640 x 480
		_sprite->setScaleX(winSize.width / _sprite->getContentSize().width);   //640 / 720
		_sprite->setScaleY(winSize.height / _sprite->getContentSize().height); //480 / 960

		bRet = true;
    } while (0);

    return bRet;
}

Background::Background()
{
}

Background::~Background(void)
{
}
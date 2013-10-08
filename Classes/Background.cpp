#include "Background.h"

using namespace cocos2d;

Background::Background(std::string backgroundFileName)
{
	//http://www.cocos2d-iphone.org/forums/topic/changing-the-aspect-fit-of-an-image-on-a-sprite-or-a-layer/
	//set up background image and scale it appropriately
	_sprite = CCSprite::create(backgroundFileName.c_str());
	_sprite->setAnchorPoint(ccp(0, 0));
	_sprite->setPosition(ccp(0, 0));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize(); //640 x 480
	_sprite->setScaleX(winSize.width / _sprite->getContentSize().width);   //640 / 720
	_sprite->setScaleY(winSize.height / _sprite->getContentSize().height); //480 / 960
}

Background::~Background(void)
{
}
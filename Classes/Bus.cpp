#include "Bus.h"
#include "GameLayer.h"

using namespace cocos2d;

bool Bus::init()
{
    bool bRet = false;
    do 
    {
		CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
		_origin = ccp(windowSize.width, 40);
		_destination = ccp(0, 40);

		float originalWidth = 300;
		float originalHeight = 161;
		_sprite = Sprite::create("vw_small.png", CCRectMake(0, 0, originalWidth, originalHeight));
		_sprite->setAnchorPoint(ccp(0,0));

		float scaleRatioY = (windowSize.height / 20) / _sprite->getContentSize().height;
		_sprite->setScaleY(scaleRatioY);
		float scaleRatioX = (windowSize.width / 9) / _sprite->getContentSize().width;
		_sprite->setScaleX(scaleRatioX);

		_speed = 100;

		bRet = true;
    } while (0);

    return bRet;
}

Bus::Bus(void)
{
}

Bus::~Bus(void)
{
}

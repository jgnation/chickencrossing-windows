#include "Log.h"
#include "GameLayer.h"

using namespace cocos2d;

bool Log::init()
{
    bool bRet = false;
    do 
    {
		CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
		_origin = ccp(windowSize.width, 40);
		_destination = ccp(0, 40);

		float originalWidth = 300;
		float originalHeight = 103;
		_sprite = CCSprite::create("plank_small.png", CCRectMake(0, 0, originalWidth, originalHeight));
		_sprite->setAnchorPoint(ccp(0,0));

		float scaleRatioY = (windowSize.height / 20) / _sprite->getContentSize().height;
		_sprite->setScaleY(scaleRatioY);
		float scaleRatioX = (windowSize.width / 4) / _sprite->getContentSize().width;
		_sprite->setScaleX(scaleRatioX);

		_speed = 100;

		bRet = true;
    } while (0);

    return bRet;
}

Log::Log(void)
{
}

Log::~Log(void)
{
}

#include "MenuLayer.h"
#include "GameLayer.h"
#include "MenuButtonLayer.h"
#include "Chicken.h"
#include "HUDLayer.h"

using namespace cocos2d;

CCScene* MenuLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MenuLayer *layer = MenuLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuLayer::init()
{
    bool bRet = false;
    do 
    {
		MenuButtonLayer * menuButtonLayer = new MenuButtonLayer();
		menuButtonLayer->init();
		this->addChild(menuButtonLayer, 5);	//z position is  on top, chicken is on 1

		bRet = true;

    } while (0);

    return bRet;
}



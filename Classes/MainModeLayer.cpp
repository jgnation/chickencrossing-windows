#include "MainModeLayer.h"

using namespace cocos2d;

MainModeLayer::MainModeLayer(void)
{
}


MainModeLayer::~MainModeLayer(void)
{
}

CCScene* MainModeLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameLayer *layer = MainModeLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

void MainModeLayer::initialChecks()
{
	if (_score >= _numEggsToCollect)
	{
		this->loadNextLevel();
	}
}
#include "EggScrambleModeLayer.h"

using namespace cocos2d;

EggScrambleModeLayer::EggScrambleModeLayer(void)
{
}


EggScrambleModeLayer::~EggScrambleModeLayer(void)
{
}

CCScene* EggScrambleModeLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameLayer *layer = EggScrambleModeLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

void EggScrambleModeLayer::initialChecks()
{
}

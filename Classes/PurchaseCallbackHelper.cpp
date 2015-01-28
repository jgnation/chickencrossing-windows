#include "PurchaseCallbackHelper.h"
#include "cocos2d.h"
#include "MenuLayer.h"
#include "MenuButtonLayer.h"
#include "MenuLayer.h"

//TODO: this is one ugly function
MenuStoreLayer* PurchaseCallbackHelper::getMenuStoreLayer()
{
    cocos2d::Scene * scene = cocos2d::CCDirector::sharedDirector()->getRunningScene();
    auto children = scene->getChildren();
    MenuLayer * menuLayer = 0;
    for(auto it = children.begin(); it != children.end(); ++it)
    {
        menuLayer = dynamic_cast<MenuLayer *>(*it);
        if (menuLayer != 0)
        {
            break;
        }
    }
    
    MenuButtonLayer * menuButtonLayer = 0;
    if (menuLayer != 0)
    {
        auto menuLayerChildren = menuLayer->getChildren();
        for (auto it = menuLayerChildren.begin(); it != menuLayerChildren.end(); ++it)
        {
            menuButtonLayer = dynamic_cast<MenuButtonLayer *>(*it);
            if (menuButtonLayer != 0)
            {
                break;
            }
        }
    }
    
    MenuStoreLayer * menuStoreLayer = 0;
    if (menuButtonLayer != 0)
    {
        auto menuButtonLayerChildren = menuButtonLayer->getChildren();
        for (auto it = menuButtonLayerChildren.begin(); it != menuButtonLayerChildren.end(); ++it)
        {
            menuStoreLayer = dynamic_cast<MenuStoreLayer *>(*it);
            if (menuStoreLayer != 0)
            {
                break;
            }
        }
    }
    
    return menuStoreLayer;
}

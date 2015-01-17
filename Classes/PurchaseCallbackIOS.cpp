#include "PurchaseCallbackIOS.h"
#include "cocos2d.h"
#include "MenuLayer.h"

void PurchaseCallbackIOS::purchaseSuccessful()
{
    cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("isPremium", true);
    cocos2d::CCDirector::sharedDirector()->replaceScene(MenuLayer::scene());
}
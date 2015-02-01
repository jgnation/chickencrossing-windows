#include "PurchaseCallbackIOS.h"
#include "cocos2d.h"
#include "MenuLayer.h"
#include "MenuButtonLayer.h"
#include "MenuLayer.h"
#include "AdmobHelper.h"
#include "PurchaseCallbackHelper.h"

//this is called on a successful purchase or restore
void PurchaseCallbackIOS::purchaseSuccessful()
{
    cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("isPremium", true);
    AdmobHelper::hideAd();
    cocos2d::CCDirector::sharedDirector()->replaceScene(MenuLayer::scene());
}

void PurchaseCallbackIOS::storeDataLoadedSuccess(std::string price)
{
    //call function in MenuStoreLayer
    MenuStoreLayer * menuStoreLayer = PurchaseCallbackHelper::getMenuStoreLayer();
    if (menuStoreLayer != 0)
    {
        menuStoreLayer->loadStoreSuccessCallback(price);
    }
}

void PurchaseCallbackIOS::storeDataLoadedFailure()
{
    //call function in MenuStoreLayer
    MenuStoreLayer * menuStoreLayer = PurchaseCallbackHelper::getMenuStoreLayer();
    if (menuStoreLayer != 0)
    {
        menuStoreLayer->loadStoreFailureCallback();
    }
}
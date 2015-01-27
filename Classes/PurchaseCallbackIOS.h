#ifndef PurchaseCallbackIOS_h
#define PurchaseCallbackIOS_h

#include "MenuStoreLayer.h"

class PurchaseCallbackIOS {
private:
    static MenuStoreLayer * getMenuStoreLayer();
public:
    static void purchaseSuccessful();
    static void storeDataLoadedSuccess(std::string price);
    static void storeDataLoadedFailure();
};

#endif

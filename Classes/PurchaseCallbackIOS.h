#ifndef PurchaseCallbackIOS_h
#define PurchaseCallbackIOS_h

#include "MenuStoreLayer.h"

class PurchaseCallbackIOS {
public:
    static void purchaseSuccessful();
    static void storeDataLoadedSuccess(std::string price);
    static void storeDataLoadedFailure();
};

#endif

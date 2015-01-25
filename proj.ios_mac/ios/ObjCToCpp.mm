#import "ObjCToCpp.h"
#import "PurchaseCallbackIOS.h"

@implementation ObjCToCpp

+ (void)purchaseSuccessful {
    PurchaseCallbackIOS::purchaseSuccessful();
}

+ (void)storeDataLoadedSuccess {
    PurchaseCallbackIOS::storeDataLoadedSuccess();
}

+ (void)storeDataLoadedFailure {
    PurchaseCallbackIOS::storeDataLoadedFailure();
}

@end
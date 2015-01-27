#import "ObjCToCpp.h"
#import "PurchaseCallbackIOS.h"

@implementation ObjCToCpp

+ (void)purchaseSuccessful {
    PurchaseCallbackIOS::purchaseSuccessful();
}

+ (void)storeDataLoadedSuccess:(NSString *) price {
    PurchaseCallbackIOS::storeDataLoadedSuccess(std::string([price UTF8String]));
}

+ (void)storeDataLoadedFailure {
    PurchaseCallbackIOS::storeDataLoadedFailure();
}

@end
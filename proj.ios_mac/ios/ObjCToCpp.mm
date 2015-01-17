#import "ObjCToCpp.h"
#import "PurchaseCallbackIOS.h"

@implementation ObjCToCpp

+ (void)purchaseSuccessful {
    PurchaseCallbackIOS::purchaseSuccessful();
}

@end
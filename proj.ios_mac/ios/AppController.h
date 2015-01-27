#import <UIKit/UIKit.h>
#import <StoreKit/StoreKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, SKProductsRequestDelegate> {
    UIWindow *window;
    NSArray *_products;
}

@property(nonatomic, readonly) RootViewController* viewController;
- (void) hideAdmobBanner;
- (void) showAdmobBanner;
- (void) showInterstitial;
- (void) validateProductIdentifiers;
- (void) initializeIAP;
- (void) requestProducts;
- (void) buyAdRemoval;
+ (NSString *) getFormattedPrice:(SKProduct *)product;

@end


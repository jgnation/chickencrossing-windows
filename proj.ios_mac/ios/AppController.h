#import <UIKit/UIKit.h>
#import <StoreKit/StoreKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, SKProductsRequestDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;
- (void) hideAdmobBanner;
- (void) showAdmobBanner;
- (void) showInterstitial;

- (void) validateProductIdentifiers;

@end


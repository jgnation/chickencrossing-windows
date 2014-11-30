#import <UIKit/UIKit.h>
#import "GADInterstitialDelegate.h"

@interface BannerViewController : UIViewController<GADInterstitialDelegate>

@property(nonatomic, strong) GADInterstitial *interstitial;
- (instancetype)initWithContentViewController:(UIViewController *)contentController;
- (void) hideBanner;
- (void) showBanner;
- (void) showInterstitial;

@end
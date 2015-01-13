#include "iOSHelper.h"
#include "AppController.h"
#include "EggScrambleIAPHelper.h"

void iOSHelper::hideAdmobBanner(){
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate hideAdmobBanner];
}

void iOSHelper::showAdmobBanner(){
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate showAdmobBanner];
}

void iOSHelper::showInterstitial(){
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate showInterstitial];
}

void iOSHelper::getAvailableItems() {
    //AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    //[appDelegate validateProductIdentifiers];
    
    [[EggScrambleIAPHelper sharedInstance] requestProductsWithCompletionHandler:^(BOOL success, NSArray *products) {
        if (success) {
            NSArray * _products = products;
            
            //self.products = response.products;
            NSLog(@"The ProductIdentifiers are:%@",[_products description]);
            NSArray * skProducts = _products;
            for (SKProduct * skProduct in skProducts) {
                NSLog(@"Found product: %@ %@ %0.2f",
                      skProduct.productIdentifier,
                      skProduct.localizedTitle,
                      skProduct.price.floatValue);
            }

        }
    }];
}
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
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate requestProducts];
}

void iOSHelper::buyAdRemoval() {
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate buyAdRemoval];
}

void iOSHelper::restorePurchases() {
    [[EggScrambleIAPHelper sharedInstance] restoreCompletedTransactions];
}
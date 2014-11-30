#include "iOSHelper.h"
#include "AppController.h"

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
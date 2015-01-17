

#ifndef __iOSHelper__
#define __iOSHelper__
class  iOSHelper {
    
public:
    iOSHelper() { }
    
    // Admob
    static void hideAdmobBanner();
    static void showAdmobBanner();
    static void showInterstitial();
    
    //App store
    static void getAvailableItems();
    static void buyAdRemoval();
};

#endif
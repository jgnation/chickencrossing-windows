#import "EggScrambleIAPHelper.h"

@implementation EggScrambleIAPHelper

+ (EggScrambleIAPHelper *)sharedInstance {
    static dispatch_once_t once;
    static EggScrambleIAPHelper * sharedInstance;
    dispatch_once(&once, ^{
        NSSet * productIdentifiers = [NSSet setWithObjects:
                                      @"com.jgnation.eggscramble.adremoval",
                                      nil];
        sharedInstance = [[self alloc] initWithProductIdentifiers:productIdentifiers];
    });
    return sharedInstance;
}

@end
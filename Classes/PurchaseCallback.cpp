#include "PurchaseCallback.h"
#include "cocos2d.h"
#include "MenuLayer.h"
#include "PurchaseCallbackHelper.h"
#include "MenuStoreLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_makePurchaseCallback(JNIEnv* env, jobject thiz, jboolean jIsSuccessful);
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_getStoreDataCallback(JNIEnv* env, jobject thiz, jstring jFormattedPrice);
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_restorePurchaseCallback(JNIEnv* env, jobject thiz);
	//JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_isPremiumCallback(JNIEnv* env, jobject thiz, jboolean jIsPremium);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_makePurchaseCallback(JNIEnv* env, jobject thiz, jboolean jIsPremium)
{
    cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("isPremium", true);
	cocos2d::CCDirector::sharedDirector()->replaceScene(MenuLayer::scene());
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_getStoreDataCallback(JNIEnv* env, jobject thiz, jstring jFormattedPrice)
{
	std::string price = cocos2d::JniHelper::jstring2string(jFormattedPrice);
	MenuStoreLayer * menuStoreLayer = PurchaseCallbackHelper::getMenuStoreLayer();
    if (menuStoreLayer != 0)
    {
        menuStoreLayer->loadStoreSuccessCallback(price);
    }
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_restorePurchaseCallback(JNIEnv* env, jobject thiz)
{
	cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("isPremium", true);
	cocos2d::CCDirector::sharedDirector()->replaceScene(MenuLayer::scene());
}

//JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_isPremiumCallback(JNIEnv* env, jobject thiz, jboolean jIsPremium);
//{
//}


#endif
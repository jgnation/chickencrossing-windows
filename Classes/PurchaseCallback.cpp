#include "PurchaseCallback.h"
#include "cocos2d.h"
#include "MenuLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_makePurchaseCallback(JNIEnv* env, jobject thiz, jboolean jIsSuccessful);
	//JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_Cocos2dxActivity_isPremiumCallback(JNIEnv* env, jobject thiz, jboolean jIsPremium);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_makePurchaseCallback(JNIEnv* env, jobject thiz, jboolean jIsPremium)
{
    cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey("isPremium", true);
	cocos2d::CCDirector::sharedDirector()->replaceScene(MenuLayer::scene());
}

//JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_Cocos2dxActivity_isPremiumCallback(JNIEnv* env, jobject thiz, jboolean jIsPremium);
//{
//}

#endif
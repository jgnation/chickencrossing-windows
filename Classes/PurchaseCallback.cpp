#include "PurchaseCallback.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_Cocos2dxActivity_makePurchaseCallback(JNIEnv* env, jobject thiz, jboolean jIsSuccessful);
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_Cocos2dxActivity_isPremiumCallback(JNIEnv* env, jobject thiz, jboolean jIsPremium);
};

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_Cocos2dxActivity_makePurchaseCallback(JNIEnv* env, jobject thiz, jboolean jIsPremium)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("isPremium", true);
	CCDirector::sharedDirector()->replaceScene(MenuLayer::scene());
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_Cocos2dxActivity_isPremiumCallback(JNIEnv* env, jobject thiz, jboolean jIsPremium);
{

}

#endif
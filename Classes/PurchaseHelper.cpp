#include "PurchaseHelper.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
//#include <android/log.h>

const char* AppActivityClassName2 = "org/cocos2dx/cpp/AppActivity";

bool PurchaseHelper::isPremium()
{
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName2, "isPremium", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void PurchaseHelper::makePurchase()
{
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName2, "makePurchase", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

bool PurchaseHelper::isPremium()
{
}

void PurchaseHelper::makePurchase()
{
}

#else

bool PurchaseHelper::isPremium()
{
	CCLOG("isPremium() called");
	return false;
}

void PurchaseHelper::makePurchase()
{
	CCLOG("makePurchase() called");
	//do nothing
}

#endif

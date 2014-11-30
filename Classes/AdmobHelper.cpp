
/*
Copyright (c) 2014 Mudafar
GPLv3
*/


#include "AdmobHelper.h"
#include "cocos2d.h"


bool AdmobHelper::isAdShowing = true;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
//#include <android/log.h>


const char* AppActivityClassName = "org/cocos2dx/cpp/AppActivity";

void AdmobHelper::hideAd()
{
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "hideAd", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		isAdShowing = false;
	}
}

void AdmobHelper::showAd()
{
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showAd", "()V"))
	{

		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		isAdShowing = true;
	}
}

void AdmobHelper::showInterstitial()
{
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showInterstitial", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	    t.env->DeleteLocalRef(t.classID);
	}
}

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "iOSHelper.h"

void AdmobHelper::hideAd()
{
	CCLOG("hideAd() called");
	isAdShowing = false;
	return; //nothing
}

void AdmobHelper::showAd()
{
	CCLOG("showAd() called");
	isAdShowing = true;
	return; //nothing;
}

void AdmobHelper::showInterstitial()
{
    iOSHelper::showInterstitial();
}

#else


void AdmobHelper::hideAd()
{
	CCLOG("hideAd() called");
	isAdShowing = false;
	return; //nothing
}

void AdmobHelper::showAd()
{
	CCLOG("showAd() called");
	isAdShowing = true;
	return; //nothing;
}

void AdmobHelper::showInterstitial()
{
	CCLOG("showInterstitial() called");
	return; //nothing;
}

#endif


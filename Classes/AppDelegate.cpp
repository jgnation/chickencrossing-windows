#include "cocos2d.h"
#include "AppDelegate.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{/*
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	//start change screen size
	CCEGLView * eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("Hello World");
    //eglView->setFrameSize(720, 720);
	eglView->setFrameSize(640, 480);
	//eglView->setFrameSize(400, 900);
	pDirector->setOpenGLView(eglView);
	//end change screen size

	//default (without changing screen size)
    //pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = MenuLayer::scene();

    // run
    pDirector->runWithScene(pScene);
    return true;*/


	// initialize director
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	    if(!glview) {
        glview = GLView::create("Egg Scramble");
        director->setOpenGLView(glview);
    }

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MenuLayer::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

	Scene* scene = Director::getInstance()->getRunningScene();
	GameLayer* gameLayer = dynamic_cast<GameLayer*>(scene);
	if (gameLayer != 0)
	{
		gameLayer->pauseGame();
	}

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

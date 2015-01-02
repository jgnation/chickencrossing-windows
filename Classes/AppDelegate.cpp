#include "cocos2d.h"
#include "AppDelegate.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
#include "AdmobHelper.h"

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
	if(!glview) 
	{
        glview = GLView::create("Egg Scramble");
        director->setOpenGLView(glview);
    }

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	//preload audio
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Complete.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("SpaceQuest3.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Platform.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("212143__qubodup__splash-by-blaukreuz.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("253173__suntemple__retro-falling-down-sfx.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("253177__suntemple__retro-accomplished-sfx.wav");

    // create a scene. it's an autorelease object
    auto scene = MenuLayer::scene();

    // run
    director->runWithScene(scene);
	AdmobHelper::showAd();
    return true;
}

void AppDelegate::applicationWillEnterForeground() 
{
    Director::getInstance()->startAnimation();    
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::applicationDidEnterBackground() 
{
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

	Scene* scene = Director::getInstance()->getRunningScene();
    GameLayer* gameLayer = scene->getChildByName<GameLayer*>("GameLayer");
	if (gameLayer != 0)
	{
		gameLayer->pauseGame();
	}
    
    Director::getInstance()->stopAnimation();
}



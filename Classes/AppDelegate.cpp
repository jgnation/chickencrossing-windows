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

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) 
	{
        glview = GLViewImpl::create("Egg Scramble");
        director->setOpenGLView(glview);
    }

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isMute")) {
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0);
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0);
	}

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
	
	if (! CCUserDefault::sharedUserDefault()->getBoolForKey("isPremium")) {
		AdmobHelper::showAd();
	}

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



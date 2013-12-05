#ifndef __GAMEOVERLAYER_H__
#define __GAMEOVERLAYER_H__
 
#include "cocos2d.h"
 
using namespace cocos2d;

class GameOverLayer : public cocos2d::CCLayer
{
private:
	CCSprite * titleImage;
	CCMenuItemImage *arrow1;
	CCMenu* pMenu;

	std::vector<int> _highScores;
 
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init(std::vector<int> highScores);
 
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
 
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
 
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    //CREATE_FUNC(GameOverLayer);

	void nextButton1Callback(cocos2d::CCObject* pSender);

	void nextButton2Callback(cocos2d::CCObject* pSender);
};
 
#endif // __GAMEOVERLAYER_H__
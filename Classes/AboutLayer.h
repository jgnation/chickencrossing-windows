#ifndef __ABOUTLAYER_H__
#define __ABOUTLAYER_H__
 
#include "cocos2d.h"
 
using namespace cocos2d;

//http://www.raywenderlich.com/40544/cocos2d-x-tile-map-tutorial-part-2

class AboutLayer : public cocos2d::CCLayer
{
private:
    CCLabelTTF * _scoreLabel;
	CCLabelTTF * _livesLabel;
	CCLabelTTF * _levelLabel;
 
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
 
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
 
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
 
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(AboutLayer);
 
    void setScore(int score);

	void setLives(int lives);

	void setLevel(int level);

	void closeButtonCallback(CCObject* pSender);
};
 
#endif // __ABOUTLAYER_H__
#ifndef __HUDLAYER_H__
#define __HUDLAYER_H__
 
#include "cocos2d.h"
 
using namespace cocos2d;

//http://www.raywenderlich.com/40544/cocos2d-x-tile-map-tutorial-part-2

class HudLayer : public cocos2d::CCLayer
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
    CREATE_FUNC(HudLayer);
 
    void setScore(int score);

	void setLives(int lives);

	void setLevel(int level);

	void createScoreLabel();
	void createLivesLabel();
	void createLevelLabel();
};
 
#endif // __HUDLAYER_H__
#ifndef __LEVEL_SELECT_LAYER_H__
#define __LEVEL_SELECT_LAYER_H__

#include "cocos2d.h"
 
using namespace cocos2d;


class LevelSelectLayer : public cocos2d::CCLayer
{
private:
    CCMenu* _mainMenu;
	CCMenu* _aboutMenu;
 
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
 
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();

 
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(LevelSelectLayer);

	// a selector callback
    void number1Callback(CCObject* pSender);
	void number2Callback(CCObject* pSender);
	void number3Callback(CCObject* pSender);

};
 
#endif // __LEVEL_SELECT_LAYER_H__
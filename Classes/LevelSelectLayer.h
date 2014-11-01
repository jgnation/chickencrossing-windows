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

	void levelSelectCallback(CCObject* pSender);
	CCMenuItemImage* createLevelButton(int levelNumber, const Point &position);

};
 
#endif // __LEVEL_SELECT_LAYER_H__
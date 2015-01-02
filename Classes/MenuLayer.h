#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Level.h"
#include "Vehicle.h"
//include "Box2D/Box2D.h"
class MenuLayer : public cocos2d::CCLayer
{
private:
	Level * _level;
	std::vector<Vehicle *> _vehicleList;
public:
	~MenuLayer();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(MenuLayer);

	void update(float dt);
	float getTimeTick();
};

#endif  // __MENU_LAYER_H__
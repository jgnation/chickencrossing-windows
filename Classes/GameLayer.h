#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "Vehicle.h"

class Chicken;		//forward declation //can I just include the libraries?
class Egg;
class HudLayer;
class Level;
class LevelManager;
class GameLayer : public cocos2d::CCLayer
{
private:
	int _nextVehicle;
	float _nextVehicleSpawn;
	static bool _isMoving;
	int _score;
	int _lives;
	int _levelNumber;

	HudLayer * _hudLayer;
	Chicken * _chicken;
	Egg * _egg;
	std::vector<Vehicle *> vehicleList;
	Level * _level;
	LevelManager * _levelManager;
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	void addDog();
	void startMovement(Vehicle * vehicle);
	void spriteMoveFinished(CCNode* sender);
	void spriteMoveFinished2(CCNode* sender);

	void update(float dt);
	void setInvisible(CCNode * node);
	float randomValueBetween( float low , float high );
	float getLanePixelPosition(int laneNumber);
	int getRandomLaneNumber();
	float getTimeTick();
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	int getAbsoluteValue(int num);
	void resetFlag();
	int getLaneNumber(float pixelPosition);
	void killChicken();
	void loadLevel(int levelNumber);
	void loadNextLevel();

    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);
};

#endif  
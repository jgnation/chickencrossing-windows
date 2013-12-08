#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "Vehicle.h"

//#include "GameMode.h"

class Chicken;		//forward declation //can I just include the libraries?
class Egg;
class HudLayer;
class Level;
class LevelManager;
//class GameMode;
class GameLayer : public cocos2d::CCLayer
{
private:
	int _nextVehicle;
	float _nextVehicleSpawn;
	static bool _isMoving;

	int _lives;
	int _levelNumber;


	//GameMode * _mode;
	HudLayer * _hudLayer;
	Chicken * _chicken;
	Egg * _egg;
	cocos2d::CCArray * vehicleList2;
	std::vector<Vehicle *> vehicleList;
	Level * _level;
	LevelManager * _levelManager;

	void addKeyboardSupport();

public:
		int _score;
		int _numEggsToCollect;

	virtual bool init();
	//static cocos2d::CCScene* scene();


	//The following 3 items are overriding CCLayer's methods....or is it redefining?
	//technically....I think I am overLOADING
	//static cocos2d::CCScene* scene(GameMode* gameMode);
	//static GameLayer* create(GameMode* gameMode);
	//virtual bool init(GameMode* gameMode);

    
    // a selector callback
    void menuCloseCallback(cocos2d::CCObject* pSender);

	void addDog();
	void startMovement(Vehicle * vehicle);
	void spriteMoveFinished(cocos2d::CCNode* sender);
	void spriteMoveFinished2(cocos2d::CCNode* sender);
	void spriteMoveFinished3(cocos2d::CCNode* sender);

	void update(float dt);
	void setInvisible(cocos2d::CCNode * node);
	float randomValueBetween( float low , float high );
	float getLanePixelPosition(int laneNumber);
	int getRandomLaneNumber();
	float getTimeTick();
	//void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	int getAbsoluteValue(int num);
	void resetFlag();
	int getLaneNumber(float pixelPosition);
	void killChicken();
	void resetChicken();
	void loadLevel(int levelNumber);
	void loadNextLevel();
	void gameOver();

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

    // implement the "static node()" method manually
    //CREATE_FUNC(GameLayer);

	void ridingChickenHittingEdgeOfScreen();

	virtual void initialChecks() = 0;


};

#endif  
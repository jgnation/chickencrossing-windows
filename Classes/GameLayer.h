#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Vehicle.h"
#include "Dimensions.h"
#include "TopScore.h"


class Chicken;		//forward declation //can I just include the libraries?
class Egg;
class HudLayer;
class Level;
class LevelManager;
class PauseLayer;
class GameLayer : public cocos2d::CCLayer
{
private:
	Dimensions * _dimensions;
	int _nextVehicle;
	float _nextVehicleSpawn;
	static bool _isMoving;
	bool _isGameOver;

	int _lives;

	cocos2d::CCLayer * _actionLayer;
	Chicken * _chicken;
	Egg * _egg;
	cocos2d::CCArray * vehicleList2;

	void addKeyboardSupport();

	enum ActionLayerPositions {
		BACKGROUND_POSITION = 0, 
		VEHICLES_POSITION = 1, 
		EGG_POSITION = 2
	};

	enum GameLayerPositions {
		ACTION_LAYER_POSITION = 0, 
		CHICKEN_POSITION = 1, 
		GAME_OVER_LAYER_POSITION = 3,
		HUD_LAYER_POSITION = 4,
		PAUSE_LAYER_POSITION = 5
	};

protected:
	int _levelNumber;
	std::vector<Vehicle *> vehicleList;
	Level * _level;
	LevelManager * _levelManager;
	int calculateNextLevelScore(int levelNumber);
	HudLayer * _hudLayer;
	PauseLayer * _pauseLayer;
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
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	//int getAbsoluteValue(int num);
	void resetFlag();
	void killChicken();
	void resetChicken();
	void loadLevel(int levelNumber);
	void loadNextLevel();
	void gameOver();

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

    // implement the "static node()" method manually
    //CREATE_FUNC(GameLayer);

	void ridingChickenHittingEdgeOfScreen();

	virtual void initialChecks() = 0;
	virtual std::vector<TopScore> checkHighScores() = 0;

	void pauseGame();
	void resumeGame(cocos2d::CCObject* pSender);

};

#endif  
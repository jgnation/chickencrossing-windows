#ifndef __GAMEOVERLAYER_H__
#define __GAMEOVERLAYER_H__
 
#include "cocos2d.h"
#include "TopScore.h"
 
using namespace cocos2d;

class GameOverLayer : public cocos2d::CCLayer
{
private:
	CCSprite * gameOverImage;
	CCMenuItemImage *arrow1;
	CCMenu* pMenu;

	std::vector<TopScore> _highScores;
 
public:
	static GameOverLayer* create(std::vector<TopScore> highScores);

    virtual bool init(std::vector<TopScore> highScores);
 
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
 
    // a selector callback
    void menuCloseCallback(CCObject* pSender);    

	void nextButton1Callback(cocos2d::CCObject* pSender);

	void nextButton2Callback(cocos2d::CCObject* pSender);

	void displayTopScores();
};
 
#endif // __GAMEOVERLAYER_H__
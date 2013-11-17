#include "HudLayer.h"
 
using namespace cocos2d;
 
bool HudLayer::init()
{
    if (CCLayer::init()) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
 
        _scoreLabel = new CCLabelTTF();
        _scoreLabel->initWithString("Score: 0", "Verdana-Bold", 18.0);
        _scoreLabel->setColor(ccc3(255,255,255));

		_livesLabel = new CCLabelTTF();
		_livesLabel->initWithString("Lives: 5", "Verdana-Bold", 18.0);
		_livesLabel->setColor(ccc3(255,255,255));

        int margin = 10;
        _scoreLabel->setPosition(ccp(winSize.width - (_scoreLabel->getContentSize().width/2) - margin, _scoreLabel->getContentSize().height/2 + margin));
        this->addChild(_scoreLabel);

		_livesLabel->setPosition(ccp((_scoreLabel->getContentSize().width/2) + margin, winSize.height - (_scoreLabel->getContentSize().height/2) - margin));
		this->addChild(_livesLabel);
    }
 
    return true;
}
 
void HudLayer::setScore(int score)
{
    CCString * scoreString = new CCString();
    scoreString->initWithFormat("Score: %d", score);
    _scoreLabel->setString(scoreString->getCString());
}

void HudLayer::setLives(int lives)
{
	CCString * livesString = new CCString();
    livesString->initWithFormat("Lives: %d", lives);
    _livesLabel->setString(livesString->getCString());
}
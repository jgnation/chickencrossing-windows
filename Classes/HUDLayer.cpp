#include "HudLayer.h"
 
using namespace cocos2d;
 
bool HudLayer::init()
{
    if (CCLayer::init()) {
        //for the labels I am going to want to set them at a maximum size
        //get the contentSize of that
        //then scale it to whatever it needs to be
        //the max size should have a scale of 1.0 (this will be for the retina screen)
        //I could scale the margin as well, but I don't think I NEED to.
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
 
        _scoreLabel = new CCLabelTTF();
        _scoreLabel->initWithString("Score: 0", "Verdana-Bold", 18.0);
        _scoreLabel->setColor(ccc3(255,255,255));

		_livesLabel = new CCLabelTTF();
		_livesLabel->initWithString("Lives: 5", "Verdana-Bold", 18.0);
		_livesLabel->setColor(ccc3(255,255,255));

		/*
		Note: If I initialize the string with "Level 1", the positioning of the label will be off.  This is because the subsequent update of the string
		(in this->setLevel(1) will call setString(), which will do a string comparison of the current string and the string to set.  If they are the same,
		then the label is not updated.
		*/
		_levelLabel = CCLabelTTF::create("Level 0", "Helvetica", 60.0);
		_levelLabel->setColor(ccc3(255,255,255));
		Size originalSize = _levelLabel->getContentSize();
		float scaleRatio = (winSize.height / 19.0) / originalSize.height;
		_levelLabel->setScale(scaleRatio);
		_levelLabel->setContentSize(CCSize(originalSize.width * scaleRatio, originalSize.height * scaleRatio));
		

        int margin = 10;

        _scoreLabel->setPosition(ccp(winSize.width - (_scoreLabel->getContentSize().width/2) - margin, _scoreLabel->getContentSize().height/2 + margin));
        this->addChild(_scoreLabel);

		_livesLabel->setPosition(ccp((_livesLabel->getContentSize().width/2) + margin, winSize.height - (_livesLabel->getContentSize().height/2) - margin));
		this->addChild(_livesLabel);

		_levelLabel->setAnchorPoint(ccp(1,1));
		_levelLabel->setPosition(ccp(winSize.width - margin, winSize.height - margin));
		this->addChild(_levelLabel);
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

void HudLayer::setLevel(int level)
{
	CCString * levelString = new CCString();
    levelString->initWithFormat("Level %d", level);
    _levelLabel->setString(levelString->getCString());
}
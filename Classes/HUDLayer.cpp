#include "HudLayer.h"
 
using namespace cocos2d;
 
/*
The labels are set to a font size of 60.  This is a good size for the retina screen on the iPad with a scaleRatio of 1.0.  
The font is scaled depending on screen size.

I could scale the margin as well, but I don't think I _need_ to.
*/
bool HudLayer::init()
{
    if (CCLayer::init()) {     
		this->createHighScoreLabel();
		this->createScoreLabel();
		this->createLivesLabel();
		this->createLevelLabel();    
    }
 
    return true;
}

void HudLayer::createHighScoreLabel()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	/*
	The score value must be set incorrectly at first.  See createLevelLabel() for an explanation.  This should be fixed.
	*/
    _highScoreLabel = CCLabelTTF::create("High Score: X", "Verdana-Bold", 60.0); 
    _highScoreLabel->setColor(ccc3(255,255,255));
	Size originalSize = _highScoreLabel->getContentSize();
	float laneHeight = (winSize.height / 19.0) / 2; //this /2 is so I can fit two labels in one lane
	float laneMargin = laneHeight * .05;
	float desiredLabelHeight = laneHeight - (laneMargin + laneMargin);
	float scaleRatio = desiredLabelHeight / originalSize.height;
	_highScoreLabel->setScale(scaleRatio);
	_highScoreLabel->setContentSize(CCSize(originalSize.width * scaleRatio, originalSize.height * scaleRatio));

	//_highScoreLabel->setAnchorPoint(ccp(1,1));
	//_highScoreLabel->setPosition(ccp(winSize.width - laneMargin, winSize.height - laneMargin));
	_highScoreLabel->setAnchorPoint(ccp(1,0));
	_highScoreLabel->setPosition(ccp(winSize.width - laneMargin, laneHeight + laneMargin));
    this->addChild(_highScoreLabel);

	this->setHighScore(234);
}

void HudLayer::createScoreLabel()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int margin = 10;

	/*
	The score value must be set incorrectly at first.  See createLevelLabel() for an explanation.  This should be fixed.
	*/
    _scoreLabel = CCLabelTTF::create("Score: X", "Verdana-Bold", 60.0); 
    _scoreLabel->setColor(ccc3(255,255,255));
	Size originalSize = _scoreLabel->getContentSize();
	float laneHeight = (winSize.height / 19.0) / 2;
	float laneMargin = laneHeight * .05;
	float desiredLabelHeight = laneHeight - (laneMargin + laneMargin);
	float scaleRatio = desiredLabelHeight / originalSize.height;
	_scoreLabel->setScale(scaleRatio);
	_scoreLabel->setContentSize(CCSize(originalSize.width * scaleRatio, originalSize.height * scaleRatio));

	//_scoreLabel->setAnchorPoint(ccp(1,1));
	//_scoreLabel->setPosition(ccp(winSize.width - laneMargin, winSize.height - laneHeight - laneMargin));
	_scoreLabel->setAnchorPoint(ccp(1,0));
	_scoreLabel->setPosition(ccp(winSize.width - laneMargin, laneMargin));
    this->addChild(_scoreLabel);
}

void HudLayer::createLivesLabel()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int margin = 10;

	_livesLabel = CCLabelTTF::create("Lives: X", "Verdana-Bold", 60.0);
	_livesLabel->setColor(ccc3(255,255,255));
	Size originalSize = _livesLabel->getContentSize();
	float laneHeight = (winSize.height / 19.0) / 2;
	float laneMargin = laneHeight * .05;
	float desiredLabelHeight = laneHeight - (laneMargin + laneMargin);
	float scaleRatio = desiredLabelHeight / originalSize.height;
	_livesLabel->setScale(scaleRatio);
	_livesLabel->setContentSize(CCSize(originalSize.width * scaleRatio, originalSize.height * scaleRatio));

	//_livesLabel->setAnchorPoint(ccp(0,1));
	//_livesLabel->setPosition(ccp(laneMargin, winSize.height - laneMargin));
	_livesLabel->setAnchorPoint(ccp(0,0));
	_livesLabel->setPosition(ccp(laneMargin, laneMargin));
	this->addChild(_livesLabel);

	this->setLives(5); //This is called for the same reason that the other values are set incorrectly.  The difference is that this isn't called from
	//GameLayer until the chicken dies, while the others are called on start
}

void HudLayer::createLevelLabel()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int margin = 10;

	/*
	Note: If I initialize the string with "Level 1", the positioning of the label will be off.  This is because the subsequent update of the string
	(in this->setLevel(1) will call setString(), which will do a string comparison of the current string and the string to set.  If they are the same,
	then the label is not updated.
	*/
	_levelLabel = CCLabelTTF::create("Level 0", "Helvetica", 60.0);
	_levelLabel->setColor(ccc3(255,255,255));
	Size originalSize = _levelLabel->getContentSize();
	float laneHeight = (winSize.height / 19.0) / 2;
	float laneMargin = laneHeight * .05;
	float desiredLabelHeight = laneHeight - (laneMargin + laneMargin);
	float scaleRatio = desiredLabelHeight / originalSize.height;
	_levelLabel->setScale(scaleRatio);
	_levelLabel->setContentSize(CCSize(originalSize.width * scaleRatio, originalSize.height * scaleRatio));

	//_levelLabel->setAnchorPoint(ccp(1,0));
	//_levelLabel->setPosition(ccp(winSize.width - laneMargin, laneMargin));
	_levelLabel->setAnchorPoint(ccp(0,0));
	_levelLabel->setPosition(ccp(laneMargin, laneHeight + laneMargin));
	this->addChild(_levelLabel);
}

void HudLayer::setHighScore(int score)
{
	CCString * scoreString = CCString::createWithFormat("High Score: %d", score);
    _highScoreLabel->setString(scoreString->getCString());
}
 
void HudLayer::setScore(int score)
{
	CCString * scoreString = CCString::createWithFormat("Score: %d", score);
    _scoreLabel->setString(scoreString->getCString());
}

void HudLayer::setLives(int lives)
{
	CCString * livesString = CCString::createWithFormat("Lives: %d", lives);
    _livesLabel->setString(livesString->getCString());
}

void HudLayer::setLevel(int level)
{
	CCString * levelString = CCString::createWithFormat("Level %d", level);
    _levelLabel->setString(levelString->getCString());
}
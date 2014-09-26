#include "GameOverLayer.h"
#include "MenuLayer.h"
 
using namespace cocos2d;
 
/*
Todo, for setting the top scores, I should calculate the width of the scaled TopScores image and place the scores in the box relative to that.
*/
bool GameOverLayer::init(std::vector<int> highScores)
{
    if (CCLayer::init()) {

		_highScores = highScores;

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
 
        //add game over image
		float originalWidth = 576;
		float originalHeight = 144;
		titleImage = CCSprite::create("game_over.png", CCRectMake(0, 0, originalWidth, originalHeight));
		//titleImage->setScale(.7);
		titleImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .7));
		this->addChild(titleImage);


		arrow1 = CCMenuItemImage::create(
			"arrow.png",
			"arrow.png",
			this,
			menu_selector(GameOverLayer::nextButton1Callback));

		arrow1->setScale(.5);
		// Place the menu item bottom-right conner.
		arrow1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .4));

		// Create a menu with the "close" menu item, it's an auto release object.
		pMenu = CCMenu::create(arrow1, NULL);
		pMenu->setPosition(CCPointZero);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu);
    }
 
    return true;
}

void GameOverLayer::nextButton1Callback(CCObject* pSender)
{
	//remove the game over and arrow images
	titleImage->setVisible(false);
	arrow1->setVisible(false);
	pMenu->setVisible(false);

	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	//create the TopScores box
	float originalWidth = 550;
	float originalHeight = 385;
	CCSprite * topScoresImage = CCSprite::create("top_scores.png", CCRectMake(0, 0, originalWidth, originalHeight));


	float scaleY = (windowSize.height * .5) / topScoresImage->getContentSize().height;
	float scaleX = (windowSize.width * .7) / topScoresImage->getContentSize().width;
	topScoresImage->setScaleY(scaleY);
	topScoresImage->setScaleX(scaleX);

	topScoresImage->setAnchorPoint(ccp(0,1));
	topScoresImage->setPosition(ccp(windowSize.width * .15, windowSize.height - (windowSize.height * .15)));
	this->addChild(topScoresImage);
	
	//display scores
	float yPosCoefficient = .30;
	for (int i = 0; i < _highScores.size(); i++)
	{
		std::stringstream sstm;
		sstm << (i + 1) << ". " << _highScores[i] << "\n";

		CCLabelTTF* _scoreLabel = new CCLabelTTF();
		_scoreLabel->initWithString(sstm.str().c_str(), "Verdana-Bold", 18.0);
		_scoreLabel->setColor(ccc3(0,0,0));

		_scoreLabel->setAnchorPoint(ccp(0,1));
		_scoreLabel->setPosition(ccp(windowSize.width * .25, windowSize.height - (windowSize.height * yPosCoefficient)));
		this->addChild(_scoreLabel);
		yPosCoefficient += .05;
	}

	//display next button
	CCMenuItemImage *arrow2 = CCMenuItemImage::create(
			"arrow.png",
			"arrow.png",
			this,
			menu_selector(GameOverLayer::nextButton2Callback));

	arrow2->setScale(.5);
	// Place the menu item bottom-right conner.
	arrow2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .4));

	// Create a menu with the "close" menu item, it's an auto release object.
	CCMenu* pMenu = CCMenu::create(arrow2, NULL);
	pMenu->setPosition(CCPointZero);

	// Add the menu to HelloWorld layer as a child layer.
	this->addChild(pMenu);
}

void GameOverLayer::nextButton2Callback(CCObject* pSender)
{
	CCScene *pScene = MenuLayer::scene();
    //CCScene *s = CCTransitionSplitRows::transitionWithDuration(0.5, pScene);
    //CCDirector::sharedDirector()->replaceScene(s);

	CCDirector::sharedDirector()->replaceScene(pScene);
}
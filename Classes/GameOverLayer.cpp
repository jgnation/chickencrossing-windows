#include "GameOverLayer.h"
#include "MenuLayer.h"
 
using namespace cocos2d;
 
/*
Todo, for setting the top scores, I should calculate the width of the scaled TopScores image and place the scores in the box relative to that.
OR
I could write the score text to the screen, and then set the top scores image such that it surrounds the text.  THAT would be easier.
*/
bool GameOverLayer::init(std::vector<int> highScores)
{
    if (CCLayer::init()) {

		_highScores = highScores;

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
 
        //add game over image
		float originalWidth = 576;
		float originalHeight = 144;
		gameOverImage = CCSprite::create("game_over.png", CCRectMake(0, 0, originalWidth, originalHeight));
		float scaleRatio = (winSize.width *.8) / gameOverImage->getContentSize().width;
		gameOverImage->setScale(scaleRatio);
		gameOverImage->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .6));
		this->addChild(gameOverImage);


		float originalWidthArrow = 300;
		float originalHeightArrow = 228;
		arrow1 = CCMenuItemImage::create(
			"arrow.png",
			"arrow.png",
			this,
			menu_selector(GameOverLayer::nextButton1Callback));

		float scaleRatioArrowX = (winSize.width *.2) / arrow1->getContentSize().width;
		float scaleRatioArrowY = (winSize.height *.15) / arrow1->getContentSize().height;
		arrow1->setScale(scaleRatioArrowX);
		arrow1->setScale(scaleRatioArrowY);
		arrow1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .25));

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
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//remove the game over and arrow images
	gameOverImage->setVisible(false);
	arrow1->setVisible(false);
	pMenu->setVisible(false);

	this->displayTopScores();

	//display next button
	float originalWidthArrow = 300;
	float originalHeightArrow = 228;
	CCMenuItemImage *arrow2 = CCMenuItemImage::create(
			"arrow.png",
			"arrow.png",
			this,
			menu_selector(GameOverLayer::nextButton2Callback));

	float scaleRatioArrowX = (winSize.width *.2) / arrow2->getContentSize().width;
	float scaleRatioArrowY = (winSize.height *.15) / arrow2->getContentSize().height;
	arrow2->setScale(scaleRatioArrowX);
	arrow2->setScale(scaleRatioArrowY);
	arrow2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .25));

	// Create a menu with the "close" menu item, it's an auto release object.
	CCMenu* pMenu = CCMenu::create(arrow2, NULL);
	pMenu->setPosition(CCPointZero);

	// Add the menu to HelloWorld layer as a child layer.
	this->addChild(pMenu);
}

void GameOverLayer::displayTopScores()
{	
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	//create the TopScores box
	/*float originalWidth = 550;
	float originalHeight = 385;
	CCSprite * topScoresImage = CCSprite::create("top_scores.png", CCRectMake(0, 0, originalWidth, originalHeight));

	float scaleY = (windowSize.height * .5) / topScoresImage->getContentSize().height;
	float scaleX = (windowSize.width * .7) / topScoresImage->getContentSize().width;
	topScoresImage->setScaleY(scaleY);
	topScoresImage->setScaleX(scaleX);

	topScoresImage->setAnchorPoint(ccp(0,1));
	topScoresImage->setPosition(ccp(windowSize.width * .15, windowSize.height - (windowSize.height * .15)));
	this->addChild(topScoresImage);*/
	
	CCLayerColor* backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), windowSize.width * .60, windowSize.height * .35);
	backgroundColor->setOpacity(100);
	backgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
	backgroundColor->setPosition(ccp(windowSize.width / 2, windowSize.height * .55));
	this->addChild(backgroundColor);

	//display scores
	float yCoefficient = 1.0;
	Size backgroundColorSize = backgroundColor->getContentSize();
	int numScores = _highScores.size();
	for (int i = 0; i < numScores; i++)
	{
		std::stringstream sstm;
		sstm << (i + 1) << ". " << _highScores[i];

		CCLabelTTF* scoreLabel = new CCLabelTTF();
		scoreLabel->initWithString(sstm.str().c_str(), "Verdana-Bold", 50.0);
		scoreLabel->setColor(ccc3(0,0,0));
		Size originalSize = scoreLabel->getContentSize();
		float scaleRatio = (backgroundColorSize.height / 10.0) / originalSize.height;
		scoreLabel->setScale(scaleRatio);
		scoreLabel->setContentSize(CCSize(originalSize.width * scaleRatio, originalSize.height * scaleRatio));

		scoreLabel->setAnchorPoint(ccp(0,1));
		scoreLabel->setPosition(ccp(10, backgroundColorSize.height * yCoefficient));
		backgroundColor->addChild(scoreLabel);
		yCoefficient -= .2;
	}
}

void GameOverLayer::nextButton2Callback(CCObject* pSender)
{
	CCScene *pScene = MenuLayer::scene();
    //CCScene *s = CCTransitionSplitRows::transitionWithDuration(0.5, pScene);
    //CCDirector::sharedDirector()->replaceScene(s);

	CCDirector::sharedDirector()->replaceScene(pScene);
}
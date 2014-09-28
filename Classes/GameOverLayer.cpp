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

		float scaleRatioArrow = (winSize.width *.2) / arrow1->getContentSize().width;
		arrow1->setScale(scaleRatioArrow);
		// Place the menu item bottom-right conner.
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

	float scaleRatioArrow = (winSize.width *.2) / arrow2->getContentSize().width;
	arrow2->setScale(scaleRatioArrow);
	arrow2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .25));

	// Create a menu with the "close" menu item, it's an auto release object.
	CCMenu* pMenu = CCMenu::create(arrow2, NULL);
	pMenu->setPosition(CCPointZero);

	// Add the menu to HelloWorld layer as a child layer.
	this->addChild(pMenu);
}

/*
This function is fairly terrifying to look at, but it works.  The idea is that I want to add the top scores to this, and then
I want to add the backgroundColor layer to this using the positions of the top scores.  I want the backgroundColor layer to
be created with a margin around the displayed scores.

I chose to do it this way rather than adding the scores as a parent to the backgroundColor mostly because I was unable to
easily add the scores to the background color layer relative to the TOP LEFT CORNER of the background color layer.
Position (0,0) on the background color layer is the bottom left corner.  I couldn't easily calculate the needed height of
the background color layer without adding the top scores to the screen FIRST.

This method can DEFINITELY be cleaned up.
*/
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
	
	//display scores
	float yPosCoefficient = .30;
	float originalYPosCoeffient = yPosCoefficient; //used for calculating the position of the backgroundColor layer
	float addInterval = .05;
	int numScores = _highScores.size();
	for (int i = 0; i < numScores; i++)
	{
		std::stringstream sstm;
		sstm << (i + 1) << ". " << _highScores[i];

		CCLabelTTF* scoreLabel = new CCLabelTTF();
		scoreLabel->initWithString(sstm.str().c_str(), "Verdana-Bold", 50.0);
		scoreLabel->setColor(ccc3(0,0,0));
		Size originalSize = scoreLabel->getContentSize();
		float scaleRatio = (windowSize.height / 22.0) / originalSize.height;
		scoreLabel->setScale(scaleRatio);
		scoreLabel->setContentSize(CCSize(originalSize.width * scaleRatio, originalSize.height * scaleRatio));

		scoreLabel->setAnchorPoint(ccp(0,1));
		scoreLabel->setPosition(ccp(windowSize.width * .25, windowSize.height - (windowSize.height * yPosCoefficient)));
		this->addChild(scoreLabel);
		yPosCoefficient += addInterval;
	}

	float width = windowSize.width * .60;
	float topYPos = windowSize.height - (windowSize.height * originalYPosCoeffient);
	float bottomYPos = windowSize.height - (windowSize.height * (originalYPosCoeffient + (addInterval * numScores)));
	float height = topYPos - bottomYPos + (windowSize.height * .2); //at a .1 buffer to top and bottom

	CCLayerColor* backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), width, height);
	backgroundColor->setOpacity(100);
	backgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
	backgroundColor->setAnchorPoint(ccp(0,1));
	float yPos = (windowSize.height - (windowSize.height * originalYPosCoeffient)) + windowSize.height * .1;
	backgroundColor->setPosition(ccp(windowSize.width * .20, yPos));
	this->addChild(backgroundColor);
}

void GameOverLayer::nextButton2Callback(CCObject* pSender)
{
	CCScene *pScene = MenuLayer::scene();
    //CCScene *s = CCTransitionSplitRows::transitionWithDuration(0.5, pScene);
    //CCDirector::sharedDirector()->replaceScene(s);

	CCDirector::sharedDirector()->replaceScene(pScene);
}
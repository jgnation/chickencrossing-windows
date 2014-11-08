#include "GameOverLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
 
using namespace cocos2d;
 
bool GameOverLayer::init(std::vector<TopScore> highScores)
{
    if (CCLayer::init()) {

		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("SpaceQuest-MP3.mp3", true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("SpaceQuest.mid", true);

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

	//add top scores image
	float originalWidth = 576;
	float originalHeight = 144;
	CCSprite * topScores = CCSprite::create("top_scores.png", CCRectMake(0, 0, originalWidth, originalHeight));
	float scaleRatio = (winSize.width *.7) / topScores->getContentSize().width;
	topScores->setScale(scaleRatio);
	topScores->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height * .85));
	this->addChild(topScores);

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

/*
I originally created the top score string with the CCLabelTTF class.  The logic for positioning objects of that class is broken.  I spent
hours trying to figure that out.  Using a CCLabelBMFont solved all my problems.
*/
void GameOverLayer::displayTopScores()
{	
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	//create the TopScores box	
	CCLayerColor* backgroundColor = CCLayerColor::create(ccc4(255, 255, 255, 255), windowSize.width * .60, windowSize.height * .35);
	backgroundColor->setOpacity(100);
	backgroundColor->ignoreAnchorPointForPosition(false); //for some odd reason, Layer's constructor calls ignoreAnchorPointForPosition(true)
	backgroundColor->setPosition(ccp(windowSize.width / 2, windowSize.height * .55));
	this->addChild(backgroundColor);

	//display scores
	float yCoefficient = 1.0;
	Size backgroundColorSize = backgroundColor->getContentSize();
	for (int i = 0; i < _highScores.size(); i++)
	{
		std::stringstream sstm;
		sstm << (i + 1) << ". " << _highScores[i].getScore();

		CCLabelBMFont * scoreLabel = CCLabelBMFont::create(sstm.str().c_str(), "futura-48.fnt");
		Size originalSize = scoreLabel->getContentSize();
		float scaleRatio = (backgroundColorSize.height / 10.0) / originalSize.height;
		scoreLabel->setScale(scaleRatio);
		scoreLabel->setContentSize(CCSize(originalSize.width * scaleRatio, originalSize.height * scaleRatio));
		scoreLabel->setAnchorPoint(ccp(0,1));
		scoreLabel->setPosition(ccp(10, backgroundColorSize.height * yCoefficient));
		if (_highScores[i].isScoreNew())
		{
			scoreLabel->setColor(ccc3(240, 40, 40)); 
		}
		backgroundColor->addChild(scoreLabel);
		yCoefficient -= .2;
	}
}

void GameOverLayer::nextButton2Callback(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CCScene *pScene = MenuLayer::scene();
    //CCScene *s = CCTransitionSplitRows::transitionWithDuration(0.5, pScene);
    //CCDirector::sharedDirector()->replaceScene(s);

	CCDirector::sharedDirector()->replaceScene(pScene);
}
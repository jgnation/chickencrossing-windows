#include "Chicken.h"
#include "GameScene.h"

using namespace cocos2d;

//constructor
Chicken::Chicken(void) { }

Chicken::Chicken(GameScene * gameScene)
{
	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	_xMoveDistance = windowSize.height / 16; //16 because there are 16 lanes on the background image
	_yMoveDistance = windowSize.height / 16;

	_chickenSprite = CCSprite::create("small_chicken.png", CCRectMake(0, 0, 25, 38));
	_chickenSprite->setScale((windowSize.height / 20) / _chickenSprite->getContentSize().height);
	_currentPosition.x = windowSize.width / 2;
	_currentPosition.y = (_chickenSprite->getContentSize().height / 2) - 5; //this '5' should be a scaled number
	_chickenSprite->setPosition(ccp(_currentPosition.x, _currentPosition.y));

	gameScene->addChild(_chickenSprite);

	//CCFiniteTimeAction* actionMove = CCMoveTo::create((float)3, ccp(0 - _chickenSprite->getContentSize().width/2, 100));

	//CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(gameScene, callfuncN_selector(GameScene::spriteMoveFinished));

	//_chickenSprite->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

Chicken::~Chicken(void) { }

CCSprite * Chicken::getSprite()
{
	return _chickenSprite;
}

CCPoint Chicken::getPoint()
{
	return _currentPosition;
}

void Chicken::moveUp()
{
	_currentPosition.y += _yMoveDistance;
	int x = 2;
}

void Chicken::moveDown()
{
	_currentPosition.y -= _yMoveDistance;
}

void Chicken::moveLeft()
{
	_currentPosition.x -= _xMoveDistance;
}

void Chicken::moveRight()
{
	_currentPosition.x += _xMoveDistance;
}
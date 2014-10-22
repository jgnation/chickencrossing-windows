#include "TopScore.h"

TopScore::TopScore(int score, bool isNew)
{
	this->score = score;
	this->isNew = isNew;
}

TopScore::~TopScore(void)
{
}

int TopScore::getScore()
{
	return score;
}

bool TopScore::isScoreNew()
{
	return isNew;
}

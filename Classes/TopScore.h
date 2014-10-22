#ifndef __TOP_SCORE_H__
#define __TOP_SCORE_H__

class TopScore
{
public:
	TopScore(int score, bool isNew);
	~TopScore(void);
	int getScore();
	bool isScoreNew();
private:
	int score;
	bool isNew;
};

#endif


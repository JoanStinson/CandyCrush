#ifndef __CANDYSCORE_H__
#define __CANDYSCORE_H__

#include <map>

#define INIT_SCORE 60

class CandyScore {
public:
	CandyScore();
	~CandyScore();

	int GetScore(int matches);

private:
	std::map<int, int> mapScore;
};

#endif // __CANDYSCORE_H__
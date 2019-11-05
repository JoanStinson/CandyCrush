#pragma once
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
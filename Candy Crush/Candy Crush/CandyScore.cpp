#include "CandyScore.h"

CandyScore::CandyScore() {
	int score = INIT_SCORE;
	for (int i = 0; i < 3; ++i) {
		mapScore.insert(std::pair<int, int>(i, 0));
	}
	for (int matches = 3; matches <= 6; ++matches) {
		mapScore.insert(std::pair<int, int>(matches, score));
		score *= 2;
	}
}

CandyScore::~CandyScore() {
	mapScore.clear();
}

int CandyScore::GetScore(int matches) {
	return mapScore[matches];
}

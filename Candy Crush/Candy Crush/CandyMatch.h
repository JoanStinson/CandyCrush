#pragma once

enum class Match {
	NONE, ROW, COL, BOTH
};

class CandyMatch {
private:
	Match match;
	int xBegin;
	int xEnd;
	int yBegin;
	int yEnd;

public:
	CandyMatch();
	CandyMatch(Match match, int xBegin, int xEnd, int yBegin, int yEnd);
	Match GetMatch();
	int GetXBegin();
	int GetXEnd();
	int GetYBegin();
	int GetYEnd();
};

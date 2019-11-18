#ifndef __CANDYMATCH_H__
#define __CANDYMATCH_H__

#include "Point.h"

enum class Match { 
	NONE, ROW, COL, BOTH 
};

class CandyMatch {
public:
	CandyMatch();
	CandyMatch(Match match, int xBegin, int xEnd, int yBegin, int yEnd);

	Match GetMatch() const;
	int GetXBegin() const;
	int GetXEnd() const;
	int GetYBegin() const;
	int GetYEnd() const;
	iPoint GetMatches() const;

	void SetMatches(iPoint matches);

private:
	Match match;
	int xBegin;
	int xEnd;
	int yBegin;
	int yEnd;
	iPoint matches;
};

#endif // __CANDYMATCH_H__
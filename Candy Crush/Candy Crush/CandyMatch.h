#ifndef _CANDYMATCH_H_
#define _CANDYMATCH_H_

enum class Match { NONE, ROW, COL, BOTH };

class CandyMatch {
public:
	CandyMatch();
	CandyMatch(Match match, int xBegin, int xEnd, int yBegin, int yEnd);

	Match GetMatch() const;
	int GetXBegin() const;
	int GetXEnd() const;
	int GetYBegin() const;
	int GetYEnd() const;

private:
	Match match;
	int xBegin;
	int xEnd;
	int yBegin;
	int yEnd;
};

#endif
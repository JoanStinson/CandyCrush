#include "CandyMatch.h"

CandyMatch::CandyMatch() : match(Match::NONE) {
	xBegin = xEnd = yBegin = yEnd = -1;
	matches = iPoint(0, 0);
}

CandyMatch::CandyMatch(Match match, int xBegin, int xEnd, int yBegin, int yEnd) : match(match), xBegin(xBegin), xEnd(xEnd), yBegin(yBegin), yEnd(yEnd) {
	matches = iPoint(0, 0);
}

Match CandyMatch::GetMatch() const {
	return match;
}

int CandyMatch::GetXBegin() const {
	return xBegin;
}

int CandyMatch::GetXEnd() const {
	return xEnd;
}

int CandyMatch::GetYBegin() const {
	return yBegin;
}

int CandyMatch::GetYEnd() const {
	return yEnd;
}

iPoint CandyMatch::GetMatches() const {
	return matches;
}

void CandyMatch::SetMatches(iPoint matches) {
	this->matches = matches;
}

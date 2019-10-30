#include "CandyMatch.h"

CandyMatch::CandyMatch() : match(Match::NONE) {
	xBegin = xEnd = yBegin = yEnd = -1;
}

CandyMatch::CandyMatch(Match match, int xBegin, int xEnd, int yBegin, int yEnd) : match(match), xBegin(xBegin), xEnd(xEnd), yBegin(yBegin), yEnd(yEnd) {
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

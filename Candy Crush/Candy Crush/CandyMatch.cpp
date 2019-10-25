#include "CandyMatch.h"

CandyMatch::CandyMatch() : match(Match::NONE) {
	xBegin = xEnd = yBegin = yEnd = -1;
}

CandyMatch::CandyMatch(Match match, int xBegin, int xEnd, int yBegin, int yEnd) : match(match), xBegin(xBegin), xEnd(xEnd), yBegin(yBegin), yEnd(yEnd) {

}

Match CandyMatch::GetMatch() {
	return match;
}

int CandyMatch::GetXBegin() {
	return xBegin;
}

int CandyMatch::GetXEnd() {
	return xEnd;
}

int CandyMatch::GetYBegin() {
	return yBegin;
}

int CandyMatch::GetYEnd() {
	return yEnd;
}

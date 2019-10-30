#ifndef _CANDYGRID_H_
#define _CANDYGRID_H_
#include "Candy.h"
#include "CandyMatch.h"
#include <vector>

#define LEVEL_START "Game/level.txt"
#define MIN_MATCHES 3

class CandyGrid {
public:
	CandyGrid(int rows, int cols);
	~CandyGrid();

	Candy* Get(iPoint pos) const;
	void Move(iPoint pos, iPoint newPos);
	void Swap(iPoint pos, iPoint newPos);
	CandyMatch CheckMatch(CandyType type, iPoint pos);
	void ClearFromMatch(Candy *candy, CandyMatch match);
	void ClearGrid();

private:
	int rows;
	int cols;
	std::vector<std::vector<Candy*>> grid;

private:
	void ClearMatchedCol(int col, int xBegin, int xEnd);
	void ClearMatchedRow(int row, int yBegin, int yEnd);
};

#endif
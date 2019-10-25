#pragma once
#include "Candy.h"
#include "CandyMatch.h"
#include <vector>

#define MIN_MATCHES 3

class CandyGrid {
public:
	CandyGrid(int rows, int cols);
	~CandyGrid();

public:
	void Add(Candy *candy, iPoint pos);
	Candy* Get(iPoint pos);
	void Move(iPoint pos, iPoint newPos);
	void Swap(iPoint pos, iPoint newPos);
	CandyMatch CheckMatch(CandyType type, iPoint pos);
	void ClearMatchedRow(int yBegin, int yEnd);
	void ClearMatchedCol(int xBegin, int xEnd);

private:
	int rows;
	int cols;
	std::vector<std::vector<Candy*>> grid;
};

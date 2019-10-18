#pragma once
#include "Candy.h"
#include <vector>

class CandyGrid {
public:
	CandyGrid(int rows, int cols);
	~CandyGrid();

public:
	void Add(Candy *candy, iPoint pos);
	Candy* Get(iPoint pos);
	void Move(iPoint pos, iPoint newPos);
	void Swap(iPoint pos, iPoint newPos);

private:
	int rows;
	int cols;
	std::vector<std::vector<Candy*>> grid;
};

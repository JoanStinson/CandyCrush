#include "CandyGrid.h"
#include <stdlib.h>

CandyGrid::CandyGrid(int rows, int cols) : rows(rows), cols(cols) {

	grid.reserve(rows);

	for (int i = 0; i < rows; ++i) {
		std::vector<Candy*> temp;
		for (int j = 0; j < cols; ++j) {
			Candy *newCandy = new Candy(iPoint (i, j), CandyType(rand() % CANDY_TYPES));
			temp.push_back(newCandy);
		}
		grid.push_back(temp);
	}
}

CandyGrid::~CandyGrid() {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			delete grid[i][j];
		}
		grid[i].clear();
	}
	grid.clear();
}

void CandyGrid::Add(Candy* candy, iPoint pos) {
	grid[pos.x][pos.y] = candy;
}

Candy* CandyGrid::Get(iPoint pos) {
	return grid[pos.x][pos.y];
}

void CandyGrid::Move(iPoint pos, iPoint newPos) {
	grid[newPos.x][newPos.y] = grid[pos.x][pos.y];
}

void CandyGrid::Swap(iPoint pos, iPoint newPos) {
	Candy *temp = grid[newPos.x][newPos.y];
	grid[newPos.x][newPos.y] = grid[pos.x][pos.y];
	grid[pos.x][pos.y] = temp;
}

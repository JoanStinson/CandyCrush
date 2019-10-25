#include "CandyGrid.h"
#include <stdlib.h>

CandyGrid::CandyGrid(int rows, int cols) : rows(rows), cols(cols) {

	grid.reserve(rows);

	for (int i = 0; i < rows; ++i) {
		std::vector<Candy*> temp;
		for (int j = 0; j < cols; ++j) {
			Candy *newCandy = new Candy(iPoint(i, j), CandyType(rand() % CANDY_TYPES));
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
	grid[newPos.x][newPos.y]->SetPos(pos);
	grid[pos.x][pos.y]->SetPos(newPos);

	Candy *temp = grid[newPos.x][newPos.y];
	grid[newPos.x][newPos.y] = grid[pos.x][pos.y];
	grid[pos.x][pos.y] = temp;
}

CandyMatch CandyGrid::CheckMatch(CandyType type, iPoint pos) {
	CandyMatch match;

	int xBegin;
	int xEnd;
	int yBegin;
	int yEnd;

	yBegin = yEnd = pos.y;

	// CHECK LEFT
	int matches = 1;
	for (int j = pos.y - 1; j >= 0; --j) {
		if (grid[pos.x][j]->GetType() == type) {
			++matches;
			yBegin = j;
		}
		else {
			break;
		}
	}

	// CHECK RIGHT
	for (int j = pos.y + 1; j < cols; ++j) {
		if (grid[pos.x][j]->GetType() == type) {
			++matches;
			yEnd = j;
		}
		else {
			break;
		}
	}

	if (matches >= MIN_MATCHES) {
		match = CandyMatch(Match::ROW, -1, -1, yBegin, yEnd);
	}

	xBegin = xEnd = pos.x;

	// CHECK UP
	matches = 1;
	for (int j = pos.x - 1; j >= 0; --j) {
		if (grid[j][pos.y]->GetType() == type) {
			++matches;
			xBegin = j;
		}
		else {
			break;
		}
	}

	// CHECK DOWN
	for (int j = pos.x + 1; j < rows; ++j) {
		if (grid[j][pos.y]->GetType() == type) {
			++matches;
			xEnd = j;
		}
		else {
			break;
		}
	}

	if (matches >= MIN_MATCHES) {
		if (match.GetMatch() == Match::ROW)
			match = CandyMatch(Match::BOTH, xBegin, xEnd, yBegin, yEnd);
		else match = CandyMatch(Match::COL, xBegin, xEnd, -1, -1);
	}

	return match;
}

void CandyGrid::ClearMatchedRow(int yBegin, int yEnd) {

}

void CandyGrid::ClearMatchedCol(int xBegin, int xEnd) {

}

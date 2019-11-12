#include "CandyGrid.h"
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

CandyGrid::CandyGrid(int rows, int cols) : rows(rows), cols(cols) {

	grid.reserve(rows);

	// Init grid with file
	std::string line;
	std::ifstream file;
	file.open(LEVEL_START);

	int i = 0, j;
	if (file.is_open()) {

		while (std::getline(file, line)) {
			std::vector<Candy*> temp;
			std::string token;
			std::istringstream tokenStream(line);
			j = 0;

			while (std::getline(tokenStream, token, ' ')) {
				CandyType type = CandyType(std::stoi(token));
				Candy *newCandy = new Candy(iPoint(i, j), type);
				temp.push_back(newCandy);
				++j;
			}

			grid.push_back(temp);
			++i;

		}
		file.close();
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

Candy* CandyGrid::Get(iPoint pos) const {
	return grid[pos.x][pos.y];
}

void CandyGrid::Move(iPoint pos, iPoint newPos) {
	if (pos != newPos) {
		grid[newPos.x][newPos.y] = grid[pos.x][pos.y];
		grid[newPos.x][newPos.y]->SetPos(newPos);
		grid[pos.x][pos.y] = nullptr;
	}
}

void CandyGrid::Swap(iPoint pos, iPoint newPos) {
	if (pos != newPos) {
		grid[newPos.x][newPos.y]->SetPos(pos);
		grid[pos.x][pos.y]->SetPos(newPos);

		Candy *temp = grid[newPos.x][newPos.y];
		grid[newPos.x][newPos.y] = grid[pos.x][pos.y];
		grid[pos.x][pos.y] = temp;
	}
}

CandyMatch CandyGrid::CheckMatch(CandyType type, iPoint pos) {
	CandyMatch match;

	int xBegin;
	int xEnd;
	int yBegin;
	int yEnd;

	yBegin = yEnd = pos.y;

	// CHECK LEFT
	int xMatches = 1;
	for (int j = pos.y - 1; j >= 0; --j) {
		if (grid[pos.x][j]->GetType() == type) {
			++xMatches;
			yBegin = j;
		}
		else {
			break;
		}
	}

	// CHECK RIGHT
	for (int j = pos.y + 1; j < cols; ++j) {
		if (grid[pos.x][j]->GetType() == type) {
			++xMatches;
			yEnd = j;
		}
		else {
			break;
		}
	}

	if (xMatches >= MIN_MATCHES) {
		match = CandyMatch(Match::ROW, -1, -1, yBegin, yEnd);
		match.SetMatches(iPoint(xMatches, 0));
	}

	xBegin = xEnd = pos.x;

	// CHECK UP
	int yMatches = 1;
	for (int j = pos.x - 1; j >= 0; --j) {
		if (grid[j][pos.y]->GetType() == type) {
			++yMatches;
			xBegin = j;
		}
		else {
			break;
		}
	}

	// CHECK DOWN
	for (int j = pos.x + 1; j < rows; ++j) {
		if (grid[j][pos.y]->GetType() == type) {
			++yMatches;
			xEnd = j;
		}
		else {
			break;
		}
	}

	if (yMatches >= MIN_MATCHES) {
		if (match.GetMatch() == Match::ROW) {
			match = CandyMatch(Match::BOTH, xBegin, xEnd, yBegin, yEnd);
			match.SetMatches(iPoint(xMatches, yMatches));
		}
		else {
			match = CandyMatch(Match::COL, xBegin, xEnd, -1, -1);
			match.SetMatches(iPoint(0, yMatches));
		}
	}

	return match;
}

void CandyGrid::ClearFromMatch(Candy *candy, CandyMatch match) {
	switch (match.GetMatch()) {
	case Match::COL:
		ClearMatchedCol(candy->GetPos().y, match.GetXBegin(), match.GetXEnd());
		break;

	case Match::ROW:
		ClearMatchedRow(candy->GetPos().x, match.GetYBegin(), match.GetYEnd());
		break;

	case Match::BOTH:
		ClearMatchedCol(candy->GetPos().y, match.GetXBegin(), match.GetXEnd());
		ClearMatchedRow(candy->GetPos().x, match.GetYBegin(), match.GetYEnd());
		break;
	}
}

void CandyGrid::ClearGrid() {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			Candy *candy = Get(iPoint(i, j));
			CandyMatch match = CheckMatch(candy->GetType(), candy->GetPos());
			if (match.GetMatch() != Match::NONE) {
				ClearFromMatch(candy, match);
			}
		}
	}
}

void CandyGrid::ClearMatchedCol(int col, int xBegin, int xEnd) {
	// Clear matched candies
	int pos = xEnd;
	for (int i = xBegin - 1; i >= 0; --i, --pos)
		Move(iPoint(i, col), iPoint(pos, col));

	// Generate new candies
	for (int i = pos; i >= 0; --i) {
		CandyType type = CandyType(rand() % CANDY_TYPES);
		grid[i][col] = new Candy(iPoint(i, col), type);
	}
}

void CandyGrid::ClearMatchedRow(int row, int yBegin, int yEnd) {
	for (int pos = yBegin; pos <= yEnd; ++pos)
		ClearMatchedCol(pos, row, row);
}
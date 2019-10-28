#pragma once
#include "Point.h"
#include <SDL.h>

#define CANDY_TYPES 6

enum class CandyType { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };

class Candy {
public:
	Candy(iPoint pos, CandyType type);
	CandyType GetType();
	iPoint GetPos();
	void SetPos(iPoint pos);

private:
	iPoint pos;
	CandyType type;
};
#pragma once
#include "Point.h"
#include "SDL2/include/SDL.h"

#define CANDY_TYPES 6

enum class CandyType { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };

class Candy {
public:
	Candy(iPoint pos, CandyType type);
	CandyType GetType();
	
private:
	iPoint pos;
	CandyType type;
};
#ifndef _CANDY_H_
#define _CANDY_H_
#include "Point.h"

#define CANDY_TYPES 6

enum class CandyType { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };

class Candy {
public:
	Candy(iPoint pos, CandyType type);
	CandyType GetType();
	iPoint GetPos();
	void SetPos(iPoint pos);
	void SetType(CandyType type);

private:
	iPoint pos;
	CandyType type;
};

#endif
#include "Candy.h"

Candy::Candy(iPoint pos, CandyType type) : pos(pos), type(type) {
}

CandyType Candy::GetType() {
	return type;
}


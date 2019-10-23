#include "Candy.h"

Candy::Candy(iPoint pos, CandyType type) : pos(pos), type(type) {
}

CandyType Candy::GetType() {
	return type;
}

iPoint Candy::GetPos() {
	return pos;
}

void Candy::SetPos(iPoint pos) {
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

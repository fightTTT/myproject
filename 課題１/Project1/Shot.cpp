#include "Shot.h"



Shot::Shot()
{
}

Shot::Shot(Vector2Dbl pos)
{
	_pos = pos;
}


Shot::~Shot()
{
}

void Shot::SetMove()
{
	_pos.y -= 3.0;
}

UNIT Shot::GetUnit(void)
{
	return UNIT::SHOT;
}

#include "Shot.h"
#include "common/ImageMng.h"
#include "_DebugDispOut.h"
#include "_DebugConOut.h"


Shot::Shot()
{
}

Shot::Shot(Vector2Dbl& pos)
{
	_pos = pos;
	_size = {3,8};
	Init();
}


Shot::~Shot()
{
}


void Shot::Init(void)
{
	AnimVector data;

	data.reserve(1);
	data.emplace_back(IMAGE_ID("�V���b�g")[0], 120);
	SetAnim(ANIM::NORMAL, data);
}

void Shot::SetMove()
{
	TRACE("%d\n",_pos.y);
	
	if (_pos.y + _size.y / 2 < 0)
	{
		_death = true;
	}

	_pos.y -= 3.0;
}

UNIT Shot::GetUnit(void)
{
	return UNIT::SHOT;
}

std::vector<Shared_Obj> Shot::GetShotData()
{
	return std::vector<Shared_Obj>();
}

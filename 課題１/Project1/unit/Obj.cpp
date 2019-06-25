#include "Obj.h"
#include "Player.h"
#include <DxLib.h>


Obj::Obj()
{
}


Obj::~Obj()
{
}

void Obj::Draw(int id)
{
	DrawGraph(_pos.x, _pos.y, id, true);
}

bool Obj::SetAnim(const ANIM key, const AnimVector &data)
{
	if (_animMap.find(key) == _animMap.end())
	{
		_animMap.try_emplace(key,std::move(data));
		return true;
	}
	return false;
}

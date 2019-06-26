#include "Obj.h"
#include "Player.h"
#include <DxLib.h>


Obj::Obj()
{
	_animKey = ANIM::NORMAL;
	_animCnt = 0;
	_animFram = 0;
}


Obj::~Obj()
{
}

void Obj::Draw(void)
{
	if (_animMap.find(_animKey) == _animMap.end())
	{
		return;
	}

	if (_animMap[_animKey].size() <= _animFram)
	{
		return;
	}

	if(_animCnt >= _animMap[_animKey][_animFram].second)
	{
		_animFram++;
		if (_animFram >= _animMap[_animKey].size())
		{
			_animFram = 0;
			_animCnt = 0;
		}
	}

	if (_animCnt <= _animMap[_animKey][_animFram].second)
	{
		DrawGraph(_pos.x, _pos.y, _animMap[_animKey][_animFram].first, true);
	}

	_animCnt++;
}

void Obj::Draw(int id)
{
	DrawGraph(_pos.x, _pos.y, id, true);
}

bool Obj::SetAnim(const ANIM key, AnimVector &data)
{
	// keyを見て等価のkeyを持つ要素が既に存在する場合はmoveされない
	// 要素が無かった場合はコンテナ内に要素を直接構築する
	// そのため、dataのコンストラクタは呼ばれない
	// moveしているため参照先の変数のデータはすべて失われる
	return _animMap.try_emplace(key, std::move(data)).second;
}

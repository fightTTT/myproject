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

void Obj::SetMove()
{
}

const ANIM Obj::AnimKey()const 
{
	return _animKey;
}

bool Obj::AnimKey(const ANIM animKey)
{
	if ((_animKey < ANIM::NORMAL) || (_animKey > ANIM::MAX))
	{
		return false;
	}

	_animKey = animKey;

	return true;
}

const Vector2 Obj::Pos() const
{
	return _pos;
}

void Obj::Pos(const Vector2 &pos)
{
	_pos = pos;
}

bool Obj::SetAnim(const ANIM key, AnimVector &data)
{
	// key�����ē�����key�����v�f�����ɑ��݂���ꍇ��move����Ȃ�
	// �v�f�����������ꍇ�̓R���e�i���ɗv�f�𒼐ڍ\�z����
	// ���̂��߁Adata�̃R���X�g���N�^�͌Ă΂�Ȃ�
	// move���Ă��邽�ߎQ�Ɛ�̕ϐ��̃f�[�^�͂��ׂĎ�����
	// .second��true,false��Ԃ�
	return _animMap.try_emplace(key, std::move(data)).second;
}

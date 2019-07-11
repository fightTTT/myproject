#include "Obj.h"
#include "Player.h"
#include "../_DebugDispOut.h"
#include <DxLib.h>


Obj::Obj()
{
	_animKey = ANIM::NORMAL;
	_animCnt = 0;
	_animFram = 0;
	_death = false;
	_alive = true;
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
		DrawRotaGraph(_pos.x, _pos.y,1.0,0.0, _animMap[_animKey][_animFram].first, true,false);
	}

	_DbgDrawBox(_pos.x, _pos.y, _pos.x + _size.x, _pos.y + _size.y, 0xff0000, 1);
	_DbgDrawString(_pos.x, _pos.y, "�����܂����H", 0xff00ff);
	
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

	

	if (_animKey != animKey)
	{
		_animCnt = 0;
	}
	_animKey = animKey;

	return true;
}

const Vector2 Obj::Pos() const
{
	return _pos;
}

bool Obj::IsAnimEnd()
{
	if (_animMap.find(_animKey) == _animMap.end())
	{
		return false;
	}

	if (_animMap[_animKey].size() <= _animFram)
	{
		return false;
	}


	return _animMap[_animKey][_animFram].first == -1? true:false;
}

bool Obj::Active()
{
	if (_alive)
	{
		return false;
	}

	if (IsAnimEnd())
	{
		_death = true;
	}

	return true;
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

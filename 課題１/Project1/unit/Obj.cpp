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
	// key�����ē�����key�����v�f�����ɑ��݂���ꍇ��move����Ȃ�
	// �v�f�����������ꍇ�̓R���e�i���ɗv�f�𒼐ڍ\�z����
	// ���̂��߁Adata�̃R���X�g���N�^�͌Ă΂�Ȃ�
	// move���Ă��邽�ߎQ�Ɛ�̕ϐ��̃f�[�^�͂��ׂĎ�����
	return _animMap.try_emplace(key, std::move(data)).second;
}

#include "Enemy.h"
#include <DxLib.h>
#include "../_DebugDispOut.h"
#include "../common/ImageMng.h"

Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(const Vector2& pos, const Vector2& size, int keyData)
{
	Init();
	_pos = pos;
	_size = size;
	key = keyData;
}


Enemy::~Enemy()
{
}

void Enemy::Draw(void)
{
	DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("�L����")[11], true);
}

UNIT Enemy::GetUnit(void)
{
	return UNIT::ENEMY;
}

void Enemy::SetMove()
{
	if (CheckHitKey(key))
	{
		_active = true;
	}

	_DbgDrawFormatString(0, 15, 0xff00ff, "enemyPos:%d,%d", _pos.x, _pos.y);
}

bool Enemy::Init(void)
{
	AnimVector data;

	data.reserve(2);
	//data.push_back(std::make_pair(IMAGE_ID("�L����")[0],30));

	// ��L��push_back�Ɠ�������
	data.emplace_back(IMAGE_ID("�L����")[10], 30);
	data.emplace_back(IMAGE_ID("�L����")[11], 60);

	SetAnim(ANIM::NORMAL, data);
	_active = false;

	return true;
}
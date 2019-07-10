#include <DxLib.h>
#include <time.h>
#include "Enemy.h"
#include "../_DebugDispOut.h"
#include "../common/ImageMng.h"


Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(const Vector2& pos, const Vector2& size)
{
	Init();
	_pos = pos;
	_size = size;
}


Enemy::~Enemy()
{
}

void Enemy::Draw(void)
{
	DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("ƒLƒƒƒ‰")[11], true);
}

UNIT Enemy::GetUnit(void)
{
	return UNIT::ENEMY;
}

void Enemy::SetMove()
{
	if (!_active)
	{
		return;
	}

	if (rand()%1200 == 0)
	{
		_active = false;
		AnimKey(ANIM::EX);
	}

	if (!_active)
	{
		//_death = true;
	}

	_DbgDrawFormatString(0, 15, 0xff00ff, "enemyPos:%d,%d", _pos.x, _pos.y);
}

bool Enemy::Init(void)
{
	AnimVector data;

	data.reserve(2);
	//data.push_back(std::make_pair(IMAGE_ID("ƒLƒƒƒ‰")[0],30));

	// ã‹L‚Ìpush_back‚Æ“¯‚¶ˆ—
	data.emplace_back(IMAGE_ID("ƒLƒƒƒ‰")[10], 30);
	data.emplace_back(IMAGE_ID("ƒLƒƒƒ‰")[11], 60);

	SetAnim(ANIM::NORMAL, data);

	data.reserve(5);
	data.emplace_back(IMAGE_ID("”š”j")[0], 20);
	data.emplace_back(IMAGE_ID("”š”j")[1], 40);
	data.emplace_back(IMAGE_ID("”š”j")[2], 60);
	data.emplace_back(IMAGE_ID("”š”j")[3],80);
	data.emplace_back(IMAGE_ID("”š”j")[4], 100);
	data.emplace_back(-1, 45);
	
	SetAnim(ANIM::EX, data);
	_active = true;

	return true;
}
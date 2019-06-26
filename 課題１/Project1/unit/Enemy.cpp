#include "Enemy.h"
#include <DxLib.h>
#include "../common/ImageMng.h"

Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(const Vector2& pos)
{
	Init();
	_pos = pos;
}


Enemy::~Enemy()
{
}

void Enemy::Draw(void)
{
	DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("キャラ")[11], true);
}

UNIT Enemy::GetUnit(void)
{
	return UNIT::ENEMY;
}

void Enemy::Init(void)
{
	AnimVector data;

	data.reserve(2);
	//data.push_back(std::make_pair(IMAGE_ID("キャラ")[0],30));

	// 上記のpush_backと同じ処理
	data.emplace_back(IMAGE_ID("キャラ")[10], 30);
	data.emplace_back(IMAGE_ID("キャラ")[11], 60);

	SetAnim(ANIM::NORMAL, data);
}
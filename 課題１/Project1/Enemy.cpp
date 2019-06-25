#include "Enemy.h"
#include <DxLib.h>
#include "common/ImageMng.h"

Enemy::Enemy()
{
}

Enemy::Enemy(const Vector2& pos)
{
	_pos = pos;
}


Enemy::~Enemy()
{
}

void Enemy::Draw(void)
{
	DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("ƒLƒƒƒ‰")[11], true);
}
#include "Player.h"
#include <DxLib.h>
#include "common/ImageMng.h"
#include "_DebugConOut.h"

Player::Player()
{
	
}

Player::Player(const Vector2& pos)
{
	_pos = pos;
	TRASCE("%d",_pos.x);
}


Player::~Player()
{
}

void Player::Draw(void)
{
	DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("ƒLƒƒƒ‰")[0], true);
}

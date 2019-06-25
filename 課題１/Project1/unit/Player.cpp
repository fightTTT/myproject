#include "Player.h"
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../_DebugConOut.h"

Player::Player()
{
	Init();
}

Player::Player(const Vector2& pos)
{
	Init();
	_pos = pos;
	TRASCE("%d",_pos.x);
}


Player::~Player()
{
}

void Player::Draw(void)
{
	DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("キャラ")[0], true);
}

UNIT Player::GetUnit(void)
{
	return UNIT::PLAYER;
}

bool Player::Init(void)
{
	AnimVector data;

	data.reserve(2);
	//data.push_back(std::make_pair(IMAGE_ID("キャラ")[0],30));

	// 上記のpush_backと同じ処理
	data.emplace_back(IMAGE_ID("キャラ")[0], 30);
	data.emplace_back(IMAGE_ID("キャラ")[1], 60);

	SetAnim(ANIM::NORMAL,data);

	return true;
}

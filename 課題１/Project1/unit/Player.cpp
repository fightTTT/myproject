#include "Player.h"
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../_DebugConOut.h"
#include "../_DebugDispOut.h"
#include "../Input/KeyState.h"

Player::Player()
{
	Init();
}

Player::Player(const Vector2& pos, const Vector2& size)
{
	Init();
	_pos = pos;
	_size = size;

	
	TRACE("%d",_pos.x);
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

void Player::SetMove()
{
	if (Active())
	{
		return;
	}

	if (rand() % 10 == 0)
	{
		_alive = false;
		AnimKey(ANIM::DEATH);
	}


	inputState->Update();
	if (inputState->state(INPUT_ID::LEFT).first)
	{
		_pos.x -= 2;
	}
	if (inputState->state(INPUT_ID::RIGHT).first)
	{
		_pos.x += 2;
	}
	if (inputState->state(INPUT_ID::UP).first)
	{
		_pos.y -= 2;
	}
	if (inputState->state(INPUT_ID::DOWN).first)
	{
		_pos.y += 2;
	}

	_DbgDrawFormatString(0, 0, 0xff00ff, "playerPos:%d,%d", _pos.x,_pos.y);
}

bool Player::Init(void)
{
	AnimVector data;

	data.reserve(2);
	//data.push_back(std::make_pair(IMAGE_ID("キャラ")[0],30));

	// 上記のpush_backと同じ処理
	data.emplace_back(IMAGE_ID("キャラ")[0], 30);
	data.emplace_back(IMAGE_ID("キャラ")[1], 60);

	SetAnim(ANIM::NORMAL, data);

	data.reserve(1);
	data.emplace_back(IMAGE_ID("キャラ")[2], 60);
	SetAnim(ANIM::EX,data);

	data.reserve(4);
	data.emplace_back(IMAGE_ID("PL爆破")[0],  5);
	data.emplace_back(IMAGE_ID("PL爆破")[1], 15);
	data.emplace_back(IMAGE_ID("PL爆破")[2], 25);
	data.emplace_back(IMAGE_ID("PL爆破")[3], 35);
	data.emplace_back(-1, 50);

	SetAnim(ANIM::DEATH, data);

	inputState = std::make_unique<KeyState>();

	//_animKey = ANIM::EX;

	return true;
}

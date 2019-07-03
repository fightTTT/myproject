#include "Player.h"
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../_DebugConOut.h"
#include "../Input/KeyState.h"

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
	DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("�L����")[0], true);
}

UNIT Player::GetUnit(void)
{
	return UNIT::PLAYER;
}

void Player::SetMove()
{
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
}

bool Player::Init(void)
{
	AnimVector data;

	data.reserve(2);
	//data.push_back(std::make_pair(IMAGE_ID("�L����")[0],30));

	// ��L��push_back�Ɠ�������
	data.emplace_back(IMAGE_ID("�L����")[0], 30);
	data.emplace_back(IMAGE_ID("�L����")[1], 60);

	SetAnim(ANIM::NORMAL, data);

	data.reserve(1);
	data.emplace_back(IMAGE_ID("�L����")[2], 60);

	SetAnim(ANIM::EX,data);

	inputState = std::make_unique<KeyState>();

	//_animKey = ANIM::EX;

	return true;
}

#include <DxLib.h>
#include "KeyState.h"


KeyState::KeyState()
{
}

KeyState::~KeyState()
{
}

void KeyState::Update()
{

	GetHitKeyStateAll(_buf);

	state(INPUT_ID::LEFT, { _buf[KEY_INPUT_LEFT] , state(INPUT_ID::LEFT).first });
	state(INPUT_ID::RIGHT,{ _buf[KEY_INPUT_RIGHT], state(INPUT_ID::RIGHT).first });
	state(INPUT_ID::UP,   { _buf[KEY_INPUT_UP] ,   state(INPUT_ID::UP).first });
	state(INPUT_ID::DOWN, { _buf[KEY_INPUT_DOWN] , state(INPUT_ID::DOWN).first });

}

void KeyState::GetState()
{

}
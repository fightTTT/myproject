#include <DxLib.h>
#include "KeyState.h"


KeyState::KeyState()
{
	keyVector.emplace_back();
	keyVector.emplace_back(KEY_INPUT_RIGHT);
	keyVector.emplace_back(KEY_INPUT_UP);
	keyVector.emplace_back(KEY_INPUT_DOWN);
	keyVector.emplace_back(KEY_INPUT_Z);
	keyVector.emplace_back(KEY_INPUT_X);
	keyVector.emplace_back(KEY_INPUT_A);
	keyVector.emplace_back(KEY_INPUT_S);
}

KeyState::~KeyState()
{
}

void KeyState::Update()
{
	SetOld();
	GetHitKeyStateAll(_buf);

	/*state(INPUT_ID::LEFT, { _buf[KEY_INPUT_LEFT] , state(INPUT_ID::LEFT).first });
	state(INPUT_ID::RIGHT,{ _buf[KEY_INPUT_RIGHT], state(INPUT_ID::RIGHT).first });
	state(INPUT_ID::UP,   { _buf[KEY_INPUT_UP] ,   state(INPUT_ID::UP).first });
	state(INPUT_ID::DOWN, { _buf[KEY_INPUT_DOWN] , state(INPUT_ID::DOWN).first });*/
	for (auto key : INPUT_ID())
	{
		state(key, _buf[keyVector[0].second]);
	}
	state(INPUT_ID::LEFT, _buf[KEY_INPUT_LEFT]);
	state(INPUT_ID::RIGHT, _buf[KEY_INPUT_RIGHT]);
	state(INPUT_ID::UP, _buf[KEY_INPUT_UP]);


}

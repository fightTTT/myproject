#include "InputState.h"



InputState::InputState()
{
	for (int i = 0; INPUT_ID(i) >= INPUT_ID::MAX; i++)
	{
		_state[INPUT_ID(i)].first = 0;
		_state[INPUT_ID(i)].second = 1;
	}
}

InputState::~InputState()
{
}

const KeyPair InputState::state(INPUT_ID key)const
{
	if (_state.find(key) != _state.end())
	{
		// —áŠOˆ—
		return _state.at(key);
	}

	return {0,0};
}

const KeyMap& InputState::state()const
{
	return _state;
}

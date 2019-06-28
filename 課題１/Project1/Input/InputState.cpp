#include "InputState.h"



InputState::InputState()
{
	for (auto key:INPUT_ID())
	{
		_state.try_emplace(key, KeyPair{ 0,1 });
	}

}

InputState::~InputState()
{
}

const KeyPair InputState::state(INPUT_ID key)const
{
	try
	{
		return _state.at(key);
	}
	catch (...)
	{
		throw;
	}

	if (_state.find(key) != _state.end())
	{
		return _state.at(key);
	}

	return {0,0};
}

const KeyMap& InputState::state()const
{
	return _state;
}

bool InputState::state(const INPUT_ID key, const int pair)
{
	if (_state.find(key) != _state.end())
	{
		_state[key].first = pair;
		return true;
	}
	
	return false;
}

void InputState::SetOld(void)
{
	for (auto key : INPUT_ID())
	{
		try
		{
			_state[key].second = _state[key].first;
		}
		catch(...)
		{
			_state.emplace(key, KeyPair{ 0,1 });
		}
	}
}

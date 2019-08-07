#include <_Debug/_DebugConOut.h>
#include "InputState.h"

InputState::InputState()
{
	// ‰Šú‰»
	for (auto data : INPUT_ID())
	{
		_state.try_emplace(data, KeyPair{ 0, 1 });	//	KayPair‚ğ•t‚¯‚ÄŒ^‚ğ‚Í‚Á‚«‚è‚³‚¹‚é‚Æ´×°‚ªo‚È‚¢
	}
}

InputState::~InputState()
{
}

const KeyMap & InputState::state(void) const
{
	return _state;
}

const KeyPair InputState::state(const INPUT_ID id) const
{
	// ¬Œ÷
	try
	{
		return	_state.at(id);
	}
	// ´×°‚ªo‚½‚Æ‚«
	catch (...)
	{

	}
	// 0,0‚ğ•Ô‚·(‰Šú‰»Ø½Ä(std::initializer_list))
	return{ 0, 0 };
}

bool InputState::state(const INPUT_ID id, const KeyPair pair)
{
	_state[id] = pair;

	return true;
}

bool InputState::state(const INPUT_ID id, const int data)
{
	// ”ÍˆÍÁª¯¸
	if (_state.find(id) != _state.end())
	{
		// Œ»İ‚Ìî•ñ‚ğŠi”[
		_state[id].first = data;

		return true;
	}

	return false;
}

void InputState::SetOld(void)
{
	for (auto id : INPUT_ID())
	{
		try
		{
			// 1ÌÚ‘O‚Ìî•ñ‚ğŠi”[
			_state[id].second = _state[id].first;
		}
		catch (...)
		{
			//AST();
			_state.emplace(id, KeyPair{ 0,1 });
		}
	}
}





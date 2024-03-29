#include <_Debug/_DebugConOut.h>
#include "InputState.h"

InputState::InputState()
{
	// 初期化
	for (auto data : INPUT_ID())
	{
		_state.try_emplace(data, KeyPair{ 0, 1 });	//	KayPairを付けて型をはっきりさせるとｴﾗｰが出ない
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
	// 成功
	try
	{
		return	_state.at(id);
	}
	// ｴﾗｰが出たとき
	catch (...)
	{

	}
	// 0,0を返す(初期化ﾘｽﾄ(std::initializer_list))
	return{ 0, 0 };
}

bool InputState::state(const INPUT_ID id, const KeyPair pair)
{
	_state[id] = pair;

	return true;
}

bool InputState::state(const INPUT_ID id, const int data)
{
	// 範囲ﾁｪｯｸ
	if (_state.find(id) != _state.end())
	{
		// 現在の情報を格納
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
			// 1ﾌﾚ前の情報を格納
			_state[id].second = _state[id].first;
		}
		catch (...)
		{
			//AST();
			_state.emplace(id, KeyPair{ 0,1 });
		}
	}
}





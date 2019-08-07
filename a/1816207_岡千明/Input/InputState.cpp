#include <_Debug/_DebugConOut.h>
#include "InputState.h"

InputState::InputState()
{
	// ������
	for (auto data : INPUT_ID())
	{
		_state.try_emplace(data, KeyPair{ 0, 1 });	//	KayPair��t���Č^���͂����肳����ƴװ���o�Ȃ�
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
	// ����
	try
	{
		return	_state.at(id);
	}
	// �װ���o���Ƃ�
	catch (...)
	{

	}
	// 0,0��Ԃ�(������ؽ�(std::initializer_list))
	return{ 0, 0 };
}

bool InputState::state(const INPUT_ID id, const KeyPair pair)
{
	_state[id] = pair;

	return true;
}

bool InputState::state(const INPUT_ID id, const int data)
{
	// �͈�����
	if (_state.find(id) != _state.end())
	{
		// ���݂̏����i�[
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
			// 1�ڑO�̏����i�[
			_state[id].second = _state[id].first;
		}
		catch (...)
		{
			//AST();
			_state.emplace(id, KeyPair{ 0,1 });
		}
	}
}





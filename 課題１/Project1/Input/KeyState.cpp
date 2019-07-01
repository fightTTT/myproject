#include <DxLib.h>
#include "KeyState.h"


KeyState::KeyState()
{

	// size_t...sizeof演算子によって返される符号なし整数型
	_keyCon.reserve(static_cast<size_t>(end(INPUT_ID())));
	
	_keyCon.emplace_back(KEY_INPUT_LEFT);
	_keyCon.emplace_back(KEY_INPUT_RIGHT);
	_keyCon.emplace_back(KEY_INPUT_UP);
	_keyCon.emplace_back(KEY_INPUT_DOWN);
	_keyCon.emplace_back(KEY_INPUT_Z);
	_keyCon.emplace_back(KEY_INPUT_X);
	_keyCon.emplace_back(KEY_INPUT_A);
	_keyCon.emplace_back(KEY_INPUT_S);

	// RefKeyDataのポインタを渡す→名前空間を指定する必要がある
	func = &KeyState::RefkeyData;

	//begin(INPUT_ID());
	//INPUT_ID num;
	//// 前演算のオーバーロード
	//++num;
}

KeyState::~KeyState()
{
}

void KeyState::Update()
{
	SetOld();
	GetHitKeyStateAll(_buf);

	
	(this->*func)();
}

void KeyState::RefkeyData(void)
{
	for (auto key : INPUT_ID())
	{
		state(key, _buf[_keyCon[static_cast<int>(key)]]);
	}

	if (_buf[KEY_INPUT_F1])
	{
		_keyCon.clear();
		func = &KeyState::SetKeyConfig;
	}
}

void KeyState::SetKeyConfig(void)
{
	if (CheckHitKeyAll())
	{
		_keyCon.emplace_back(WaitKey());
	}
	
	if (_keyCon.size() >= static_cast<size_t>(end(INPUT_ID())))
	{
		func = &KeyState::RefkeyData;
	}
}

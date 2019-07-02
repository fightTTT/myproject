#include <DxLib.h>
#include "KeyState.h"
#include "../_DebugConOut.h"

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

	// this->*funcに()をつける理由としては、つけなかった場合、コンパイルする際にthis->*func　()ではなく、
	// this-> (*func())としてみられるから
	(this->*func)();		
}

void KeyState::RefkeyData(void)
{
	if (_buf[KEY_INPUT_F1])
	{
		//_keyCon.clear();
		func = &KeyState::SetKeyConfig;
		TRASCE("キーコンフィグ開始");
		confID = begin(INPUT_ID());
		TRASCE("設定キー:%d\n",confID);
		return;
	}

	for (auto key : INPUT_ID())
	{
		state(key, _buf[_keyCon[static_cast<int>(key)]]);
	}
}

void KeyState::confSave(void)
{
	//FILE *file;
	//fopen_s(&file, "data/confData.map", "wb");
	//fwrite(&_keyCon, sizeof(_keyCon.capacity()), 1, file);			// fwrite(渡すデータの先頭ﾎﾟｲﾝﾀ、ﾊﾞｲﾄ数、書き込む回数、書き込むべきﾌｧｲﾙの場所)

}

void KeyState::ConfLoad(void)
{

}

void KeyState::SetKeyConfig(void)
{
	/*if (CheckHitKeyAll())
	{
		_keyCon.emplace_back(WaitKey());
	}*/

	for (auto id : INPUT_ID())
	{
		state(id, 0);
	}

	for (int id = 0; id < sizeof(_buf)/ sizeof(_buf[0]); id++)
	{
		if (_buf[id]&& lastKeyID != id 
			&& id != KEY_INPUT_F1 && id != KEY_INPUT_DELETE)
		{
			_keyCon[static_cast<int>(confID)] = id;
			lastKeyID = id;
			++confID;	
			break;
		}
	}

	if (confID >= end(INPUT_ID()))
	{

		TRASCE("キーコンフィグ終了");
		func = &KeyState::RefkeyData;
	}
}

#include <DxLib.h>
#include "KeyState.h"
#include <_Debug/_DebugConOut.h>

struct DataHeader {
	int size;				// ｷｰの数
};

#define _FILE_ID

KeyState::KeyState()
{
	// 容量の確保
	_keyCon.reserve(static_cast<size_t>(end(INPUT_ID())));

	// 要素の追加
	//_keyCon.emplace_back(KEY_INPUT_LEFT);
	//_keyCon.emplace_back(KEY_INPUT_RIGHT);
	//_keyCon.emplace_back(KEY_INPUT_UP);
	//_keyCon.emplace_back(KEY_INPUT_DOWN);
	//_keyCon.emplace_back(KEY_INPUT_Z);
	//_keyCon.emplace_back(KEY_INPUT_X);
	//_keyCon.emplace_back(KEY_INPUT_A);
	//_keyCon.emplace_back(KEY_INPUT_S);

	// ｷｰｽﾃｰﾄｸﾗｽのﾄﾘｶﾞｰ処理の初期化
	for (auto data : _oldBuf)
	{
		_oldBuf[data] = 0;
	}

	// 初期化
	DefKey();

	// ｷｰｺﾝﾌｨｸﾞ用変数の初期値
	confID = begin(INPUT_ID());

	// 関数ﾎﾟｲﾝﾀｰ初期値
	func = &KeyState::RefKeyData;
}

KeyState::~KeyState()
{
}

void KeyState::UpDate(void)
{
	// ｷｰ情報更新
	SetOld();

	// ﾄﾘｶﾞｰ処理用
	for (int i = 0; i < sizeof(_buf) / sizeof(_buf[0]); i++)
	{
		_oldBuf[i] = _buf[i];
	}

	// ｷｰ情報取得
	GetHitKeyStateAll(_buf);

	// ｽﾃｰﾄ維持
	(this->*func)();

}

void KeyState::RefKeyData(void)
{
	// 矢印ｷｰ登録
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_keyCon[static_cast<int>(id)]]);
	}

	// ｽﾃｰﾄ切り替え
	if (_buf[KEY_INPUT_F1])
	{
		// 
		confID = begin(INPUT_ID());

		// ｷｰｺﾝﾌｨｸﾞ
		func = &KeyState::SetKeyConfig;

		// ﾃﾞﾊﾞｯｸﾛｸﾞ
		TRASE("ｷｰｺﾝﾌｨｸﾞ開始\n");
	}

	if (_buf[KEY_INPUT_F2] && !_oldBuf[KEY_INPUT_F2])
	{
		// 保存したﾃﾞｰﾀ読み込み
		KyeLoad();
	}

	if (_buf[KEY_INPUT_DELETE] && !_oldBuf[KEY_INPUT_DELETE])
	{
		// ｷｰ初期化
		DefKey();
	}
}

void KeyState::SetKeyConfig(void)
{
	// 一旦0にする
	for (auto id : INPUT_ID())
	{
		state(id, 0);
	}

	// 全体の容量から1つの容量を割って全体の総数を出す
	for (int id = 0; id < sizeof(_buf) / sizeof(_buf[0]); id++)
	{
		// ｷｰ入力があり､前のｷｰと重複しない、
		if (_buf[id] && lastKeyID != id && id != KEY_INPUT_F1 && id != KEY_INPUT_DELETE)
		{
			// ｷｰ登録
			_keyCon[static_cast<size_t>(confID)] = id;

			// 最後のｷｰ登録
			lastKeyID = id;

			// 進める
			++confID;

			// ﾃﾞﾊﾞｯｸｳｨﾝﾄﾞｳ
			TRASE("%d\n", confID);

			if (confID >= (end(INPUT_ID())))
			{
				// ｷｰｺﾝﾌｨｸﾞ用変数を初期値にする
				confID = begin(INPUT_ID());

				// ﾃﾞｰﾀ保存
				KeySave();

				// ｽﾃｰﾄ切り替え
				func = &KeyState::RefKeyData;

				// ﾃﾞﾊﾞｯｸｳｨﾝﾄﾞｳ
				TRASE("ｷｰｺﾝﾌｨｸﾞ終了\n");
			}

			break;
		}
	}

	// 変更取り消し
	if (_buf[KEY_INPUT_DELETE])
	{
		// 初期化
		confID = begin(INPUT_ID());

		// ｷｰの初期化
		DefKey();

		// ｽﾃｰﾄ切り替え
		func = &KeyState::RefKeyData;

		// ﾃﾞﾊﾞｯｸﾛｸﾞ
		TRASE("ｷｰｺﾝﾌｨｸﾞ取り消し\n");
	}
}

void KeyState::DefKey(void)
{
	// ﾃﾞﾌｫﾙﾄのｷｰ登録
	_keyCon = {
		KEY_INPUT_LEFT,
		KEY_INPUT_RIGHT,
		KEY_INPUT_UP,
		KEY_INPUT_DOWN,
		KEY_INPUT_Z,
		KEY_INPUT_X,
		KEY_INPUT_A,
		KEY_INPUT_S
	};

	// ﾃﾞﾊﾞｯｸﾛｸﾞ
	TRASE("ｷｰはﾃﾞﾌｫﾙﾄです\n");
}

bool KeyState::KeySave(void)
{
	// ﾌｧｲﾙ用ﾎﾟｲﾝﾀｰ
	FILE *file = nullptr;

	// ﾌｧｲﾙ開く(書き込みﾓｰﾄﾞ)
	fopen_s(&file, "data/keydata.dat", "wb");

	// ﾌｧｲﾙがなかったらfalseを返す
	if (&file == nullptr)
	{
		TRASE("ｾｰﾌﾞｴﾗ-\n");

		return false;
	}
	else
	{
		// 先頭、ｻｲｽﾞ、書き込み回数、ﾌｧｲﾙのﾊﾝﾄﾞﾙ
		fwrite(_keyCon.data(), _keyCon.size() * sizeof(_keyCon[0]), 1, file);

		TRASE("ｾｰﾌﾞしました\n");
	}

	// ﾌｧｲﾙを閉じる
	fclose(file);

	return true;
}

bool KeyState::KyeLoad(void)
{
	// ﾌｧｲﾙ用ﾎﾟｲﾝﾀｰ
	FILE *file = nullptr;

	// ﾌｧｲﾙ開く(読み取りﾓｰﾄﾞ)
	fopen_s(&file, "data/keydata.dat", "rb");

	// ﾌｧｲﾙがなかったらfalseを返す
	if (&file == nullptr)
	{
		TRASE("ﾛｰﾄﾞｴﾗ-\n");

		return false;
	}
	else
	{
		// ここで読み込み
		fread(_keyCon.data(), _keyCon.size() * sizeof(_keyCon[0]), 1, file);

		TRASE("ﾛｰﾄﾞしました\n");
	}

	// ﾌｧｲﾙ閉じる
	fclose(file);

	return true;
}

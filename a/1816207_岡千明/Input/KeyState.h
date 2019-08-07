#pragma once
#include <vector>
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();

	void UpDate(void)override;		// 状態更新用関数

private:
	void DefKey(void);				// ｷｰ配置初期化用

	void RefKeyData(void);			// ｷｰ情報更新用関数
	void SetKeyConfig(void);		// ｷｰｺﾝﾌｨｸﾞ用関数
	INPUT_ID confID;				// ｷｰｺﾝﾌｨｸﾞ用ID
	int lastKeyID;					// ｺﾝﾌｨｸﾞで最後に入力したｷｰを入れる(重複防止用)

	bool KeySave(void);				// ｷｰ情報ｾｰﾌﾞ用関数
	bool KyeLoad(void);				// ｷｰ情報ﾛｰﾄﾞ用関数

	char _buf[256];					// ｷｰ情報取得用
	char _oldBuf[256];				// ﾄﾘｶﾞｰ処理用

	std::vector<int>_keyCon;		// ｷｰ入力用vector

	void(KeyState::*func)(void);	// 関数ﾎﾟｲﾝﾀｰ(ﾒﾝﾊﾞｰ関数へのﾎﾟｲﾝﾀｰ)
};


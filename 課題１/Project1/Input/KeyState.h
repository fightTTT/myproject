#pragma once
#include <vector> 
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void)override;
	
private:
	char _buf[256];					// キーボードのすべてのキーの押下状態を格納している配列
	std::vector<int> _keyCon;		// キー情報を管理しているvector
	std::vector<int> _keyCondef;	// キーコンフィグのデフォルト

	// キーコンフィグとプレイヤー操作の切り替え
	void (KeyState::*func)(void);	// メンバ関数ポインタ...名前空間を指定する
	
	// キー入力更新
	void RefkeyData(void);	

	// キーコンフィグ情報セーブ
	void confSave(void);
	// キーコンフィグ情報ロード
	void ConfLoad(void);

	// キーコンフィグを行う
	void SetKeyConfig(void);
	

	INPUT_ID confID;	// キーコンフィグの種類の情報を入れる
	int lastKeyID;		// キーコンフィグで最後に入力したキー
};


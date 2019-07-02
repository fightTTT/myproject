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

	// メンバ関数ポインタ...名前空間を指定する
	void (KeyState::*func)(void);	// キーコンフィグとプレイヤー操作の切り替え
	
	// キー入力更新
	void RefkeyData(void);	
	void confSave(void);
	void ConfLoad(void);

	// キーコンフィグを行う
	void SetKeyConfig(void);
	

	INPUT_ID confID;
	int lastKeyID;
};


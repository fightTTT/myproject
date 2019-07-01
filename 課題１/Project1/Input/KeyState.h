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
	char _buf[256];
	std::vector<int> _keyCon;
	void (KeyState::*func)(void);		// メンバ関数ポインタ...名前空間を指定する
	void RefkeyData(void);
	void SetKeyConfig(void);
};


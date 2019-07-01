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
	void (KeyState::*func)(void);		// �����o�֐��|�C���^...���O��Ԃ��w�肷��
	void RefkeyData(void);
	void SetKeyConfig(void);
};


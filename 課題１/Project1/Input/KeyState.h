#pragma once
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void)override;
	void GetState(void)override;

private:
	char _buf[256];
};


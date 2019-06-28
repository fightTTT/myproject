#pragma once
#include <vector> 
#include <array>
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
	std::vector<std::array<int,int(INPUT_ID::MAX)>> keyVector;
};


#pragma once
#include "Obj.h"
class Player :
	public Obj
{
public:
	Player();
	Player(const Vector2& pos);
	~Player();
	void Draw(void) override;
	
};


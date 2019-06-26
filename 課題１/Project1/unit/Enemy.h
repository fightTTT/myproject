#pragma once
#include "Obj.h"
class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(const Vector2& pos);
	~Enemy();
	void Draw(void) override;	// overrideと書くことによってオーバーライドし忘れによるバグを防止する
	UNIT GetUnit(void) override;
private:
	void Init(void);
};


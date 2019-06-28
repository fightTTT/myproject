#pragma once
#include "Obj.h"
class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(const Vector2& pos);
	~Enemy();

	// overrideと書くことによってオーバーライドし忘れによるバグを防止する
	void Draw(void) override;	
	UNIT GetUnit(void) override;
	void SetMove();
private:
	bool Init(void);
};


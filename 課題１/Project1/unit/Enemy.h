#pragma once
#include <tuple>
#include "Obj.h"

enum class ENM_DATA
{
	POS,
	TYPE,
	SIZE,
	TARGTPOS
};

enum class ENM_TYPE
{
	A,
	B,
	C
};

using EnemyData = std::tuple<Vector2, ENM_TYPE, Vector2,Vector2>
;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(const Vector2& pos, ENM_TYPE type, const Vector2& size,const Vector2& targetPos);
	~Enemy();

	// overrideと書くことによってオーバーライドし忘れによるバグを防止する
	void Draw(void) override;	
	UNIT GetUnit(void) override;
	void SetMove();
private:
	bool Init(void);
	ENM_TYPE _type;
	Vector2 _targetPos;
};

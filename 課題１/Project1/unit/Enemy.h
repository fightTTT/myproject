#pragma once
#include <tuple>
#include <vector>
#include "Obj.h"

enum class ENM_DATA
{
	POS,
	TYPE,
	SIZE,
	TARGTPOS,
	MAX
};

enum class ENM_TYPE
{
	A,
	B,
	C,
	MAX
};

enum class MOVE_TYPE
{
	SIGMOID,
	B,
	LR,
	MAX
};

using EnemyData = std::tuple<Vector2Dbl, ENM_TYPE, Vector2,Vector2Dbl>;
using MoveType = std::tuple<Vector2Dbl, MOVE_TYPE>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyData data);
	~Enemy();

	// overrideと書くことによってオーバーライドし忘れによるバグを防止する
	void Draw(void) override;	
	UNIT GetUnit(void) override;
	void SetMove();
private:
	bool Init(void);
	void MoveSigmoid(void);
	void MoveB(void);
	void MoveLR(void);
	void (Enemy::*move)(void);	// メンバ関数ポインタ
	ENM_TYPE _type;				// 敵の種類
	Vector2Dbl _targetPos;			// 敵が並ぶ場所
	Vector2Dbl _firstTarget;		// 敵が最初に向かう場所
	int speed;
	bool firstFlag;
	int waitCnt;

	Vector2Dbl _posOld;
	static int animCnt;
	std::vector<MoveType> moveData;
	//-----------------
	float _floatPosX;
	float _floatPosY;
	//-----------------
};

#pragma once
#include <tuple>
#include <vector>
#include<list>
#include <memory>
#include "Obj.h"

enum class ENM_DATA
{
	POS,
	TYPE,
	SIZE,
	TARGTPOS,
	ENEMCNT,
	ENEMNUM,
	MAX
};

enum class ENM_TYPE
{
	A,
	B,
	C,
	MAX
};

using EnemyData = std::tuple<Vector2Dbl, ENM_TYPE, Vector2Dbl,Vector2Dbl,int,int>;

class EnemyMove;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyData& data);
	~Enemy();

	// overrideと書くことによってオーバーライドし忘れによるバグを防止する
	void Draw(void) override;	
	UNIT GetUnit(void) override;
	void SetMove();
	std::vector<Shared_Obj> GetShotData() override;

private:
	bool Init(void);
	void EnemDamage(void);		// ダメージを受けたときの処理。敵の色を変え、ライフがゼロになったら殺す

	ENM_TYPE _type;				// 種類
	Vector2Dbl _targetPos;		// 並ぶ場所

	
	int _enemCnt;

	Vector2Dbl _posOld;
	int enemNum;
	Vector2Dbl _vel;
	bool leftFlag; 
	int enemyAnimFrame;
	std::unique_ptr<EnemyMove> enemMoveData;

	//-----------------
	Vector2Dbl InstancePos;
	//-----------------
};

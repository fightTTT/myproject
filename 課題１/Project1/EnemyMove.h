#pragma once
#include "unit/Enemy.h"
#include "common/Vector2.h"

enum class MOVE_TYPE
{
	SIGMOID,
	SPIRAL,
	LR,
	MAX
};

using MoveType = std::tuple<Vector2Dbl, MOVE_TYPE>;

class EnemyMove
{
public:
	EnemyMove();
	EnemyMove(EnemyData enemData);
	~EnemyMove();

	void Init(void);

	void SetMove(void);

	// シグモイド曲線で動く
	void MoveSigmoid(void);
	// 回転
	void MoveSpiral(void);
	// 最後の目標地点に向かう
	void MoveLastTarget(void);
	// 左右移動
	void MoveLR(void);
	// 敵の編隊のwait関数
	void MoveWait(void);

	const Vector2Dbl GetPos(void) { return _pos; };
	const float GetAngle(void) { return _angle; };


private:
	static bool enemGather;

	Vector2Dbl _pos;
	Vector2Dbl _posOld;
	Vector2Dbl _vel;
	Vector2Dbl _size;
	Vector2Dbl _targetPos;
	void (EnemyMove::*move)(void);	// メンバ関数ポインタ
	float _angle;
	std::vector<MoveType> moveData;
	bool leftFlag;
	int _enemNum;
	double speed;
	int _enemCnt;

	
	

	double X;
	double sigmoidStep;
	Vector2Dbl InstancePos;

};


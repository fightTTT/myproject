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

using MoveType = std::tuple<Vector2Dbl, MOVE_TYPE>;		// それぞれの移動の目標地点		移動方法

class EnemyMove
{
public:
	EnemyMove();
	EnemyMove(EnemyData enemData);
	~EnemyMove();

	void Init(void);

	void SetMove(void);

	const Vector2Dbl GetPos(void) { return _pos; };
	const float GetAngle(void) { return _angle; };


private:
	static bool enemGather;

	// 敵の編隊のwait関数
	void MoveWait(void);
	// シグモイド曲線で動く
	void MoveSigmoid(void);
	// 回転
	void MoveSpiral(void);
	// 最後の目標地点に向かう
	void MoveLastTarget(void);
	// 左右移動
	void MoveLR(void);

	void MoveAttack(void);
	

	Vector2Dbl _pos;
	Vector2Dbl _posOld;
	Vector2Dbl _vel;
	Vector2Dbl _size;
	Vector2Dbl _targetPos;
	void (EnemyMove::*move)(void);	// メンバ関数ポインタ
	float _angle;
	std::vector<MoveType> moveData;	 // 移動方法と目標地点を格納するvector
	bool leftFlag;					// 敵が左側から出現するとtrueにする
	int _enemNum;
	double speed;
	int _enemCnt;

	bool virtualMoveFlag;			// 攻撃時にtrueにするフラグ
	Vector2Dbl virtualMovePos;		// 攻撃時の拡大縮小の自分の座標

	double X;
	double sigmoidStep;
	Vector2Dbl InstancePos;

};


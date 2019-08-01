#pragma once
#include "unit/Enemy.h"

class EnemyMove
{
public:
	EnemyMove();
	EnemyMove(EnemyData enemData);
	~EnemyMove();

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


};


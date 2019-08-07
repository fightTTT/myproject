#include <stdio.h>

// レーザーの各部分を表す構造体
typedef struct LASER_STRUCT {
	float X, Y;                 // 座標
	float VX, VY;               // 速度
	float OldX, OldY;           // 古い座標
	float Angle;                // 回転角度
	float OldAngle;             // 古い回転角度
	struct LASER_STRUCT* Prec;  // 1つ前の部分へのポインタ
	                            // （先頭部分の場合にはNULL）
} LASER_TYPE;

void MoveHoming(LASER_TYPE* laser);
LASER_TYPE* NewLaserType();

// レーザーを動かす関数
void MoveHomingLaser(
	LASER_TYPE* laser  // レーザーの先頭部分または尾の1部分
) {
	// 先端部分の場合：
	// 誘導弾の動きと同じ。
	// 誘導の具体的な処理はMoveHoming関数で行うとする。
	if (laser->Prec==NULL) {
		MoveHoming(laser);
	}

	// 先端部分以外の場合：
	// 1つ前の部分を追いかける。
	// 古い座標と古い回転角度をコピーする。
	else {
		laser->X=laser->Prec->OldX;
		laser->Y=laser->Prec->OldY;
		laser->Angle=laser->Prec->OldAngle;
	}
}

// レーザーの発射
void ShootHomingLaser(
	float x, float y,   // 発射地点の座標
	int length          // レーザーの長さ
) {
	LASER_TYPE* laser;      // レーザーを表す構造体へのポインタ
	LASER_TYPE* prec=NULL;  // 1つ前の部分を指すポインタ
	
	// レーザーの各部分を作る：
	// レーザーの構造体を確保し，座標を初期化する。
	// 構造体確保の具体的な処理はNewLaserType関数で行うとする。
	for (int i=0; i<length; i++, prec=laser) {
		laser=NewLaserType();
		laser->X=laser->OldX=x;
		laser->Y=laser->OldY=y;
		laser->Angle=laser->OldAngle=0;

		// 尾の部分は1つ前の部分を参照するようにし，
		// 先端部分にはNULLを参照させる。
		laser->Prec=prec;
	}
}


#include <stdio.h>

// ミサイルの各部分を表す構造体
typedef struct MISSILE_STRUCT {
	float X, Y;                   // 座標
	float VX, VY;                 // 速度
	float OldX, OldY;             // 古い座標
	float Angle;                  // 回転角度
	float OldAngle;               // 古い回転角度
	struct MISSILE_STRUCT* Prec;  // 1つ前の部分へのポインタ
	                              // （先頭部分の場合にはNULL）
	bool IsMissile;               // ミサイルかどうか
	                              // （trueならミサイル，
	                              //   falseなら煙）
} MISSILE_TYPE;

MISSILE_TYPE* NewMissileType();

// ミサイルの発射
void ShootMissile(
	float x, float y,   // 発射地点の座標
	int length          // レーザーの長さ
) {
	MISSILE_TYPE* missile;    // ミサイルの構造体へのポインタ
	MISSILE_TYPE* prec=NULL;  // 1つ前の部分を指すポインタ
	
	// ミサイルの各部分を作る：
	// ミサイルの構造体を確保し，座標を初期化する。
	// 構造体確保の具体的な処理はNewMissileType関数で行うとする。
	for (int i=0; i<length; i++, prec=missile) {
		missile=NewMissileType();
		missile->X=missile->OldX=x;
		missile->Y=missile->OldY=y;
		missile->Angle=missile->OldAngle=0;

		// 尾の部分は1つ前の部分を参照するようにし，
		// 先端部分にはNULLを参照させる。
		missile->Prec=prec;

		// 先端部分はミサイルに，他の部分は煙にする。
		missile->IsMissile=(i==0);
	}
}


// ボスを表す構造体
#define MAX_PART 32
#define MAX_FORM 8
typedef struct BOSS_STRUCT {
	float X, Y;                  // ボスの座標
	struct BOSS_STRUCT* 
		Part[MAX_PART];          // ボスを構成するパーツ（ボス）
	int NumPart;                 // パーツの数
	float 
		PX[MAX_PART][MAX_FORM],  // パーツの相対座標
		PY[MAX_PART][MAX_FORM];  // [パーツ番号][形態番号]
} BOSS;

// 変形：
// 各パーツを変形前の位置から変形後の位置へ移動させる。
// 変形に掛かる時間とタイマーとの比率から，
// 移動途中の位置を計算する。
#define TRANSFORM_TIME 180
void TransformBoss(
	BOSS* boss,  // ボスの構造体へのポインタ
	int from,    // 変形前の形態番号
	int to,      // 変形後の形態番号
	int& timer   // タイマー
) {
	float ratio=(float)timer/TRANSFORM_TIME;
	for (int i=0; i<boss->NumPart; i++) {
		boss->Part[i]->X=
			boss->PX[i][from]*(1-ratio)+
			boss->PX[i][to]*ratio;
		boss->Part[i]->Y=
			boss->PY[i][from]*(1-ratio)+
			boss->PY[i][to]*ratio;
	}
}


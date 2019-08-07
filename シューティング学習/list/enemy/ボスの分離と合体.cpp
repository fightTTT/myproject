// ボスを表す構造体
#define MAX_PART 32
typedef struct BOSS_STRUCT {
	float X, Y;          // ボスの座標
	struct BOSS_STRUCT* 
		Part[MAX_PART];  // ボスを構成するパーツ（ボス）
	int NumPart;         // パーツの数
	float PX[MAX_PART], 
		PY[MAX_PART];    // パーツの相対座標
} BOSS;

void MoveBoss(BOSS* boss);

// 分離中の動き：
// 各パーツを独立に動かす。
// 移動の具体的な処理はMoveBoss関数で行うとする。
void MoveSeparatedBoss(BOSS* boss) {
	for (int i=0; i<boss->NumPart; i++) {
		MoveBoss(boss->Part[i]);
	}
}

// 合体中の動き：
// 全パーツが一体化して動くように，
// 中心となる座標に対して固定の位置にパーツを配置する。
// 移動の具体的な処理はMoveBoss関数で行うとする。
void MoveUnitedBoss(BOSS* boss) {
	MoveBoss(boss);
	for (int i=0; i<boss->NumPart; i++) {
		boss->Part[i]->X=boss->X+boss->PX[i];
		boss->Part[i]->Y=boss->Y+boss->PY[i];
	}
}


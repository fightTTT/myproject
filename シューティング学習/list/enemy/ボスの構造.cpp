// 敵を表す構造体
typedef struct {
	float X, Y;  // 敵の座標
} ENEMY;

// ボス（複雑な構造の敵）を表す構造体
#define MAX_PART 32
typedef struct {
	float X, Y;             // ボスの座標
	ENEMY* Part[MAX_PART];  // ボスを構成するパーツ（敵）
	int NumPart;            // パーツ（敵）の数
	bool Fatal[MAX_PART];   // 致命的なパーツかどうか
} COMPLEX_ENEMY;

void MoveEnemy(ENEMY* enemy);
void DrawEnemy(ENEMY* enemy, float x, float y);
bool Destroyed(ENEMY* enemy);
void DeleteEnemy(ENEMY* enemy);
void DeleteEnemy(COMPLEX_ENEMY* enemy);

// ボスの動き：
// ボスを構成する全ての敵について順に処理を行う。
void MoveComplexEnemy(COMPLEX_ENEMY* ce) {
	for (int i=0; i<ce->NumPart; i++) {

		// 敵の行動：
		// 具体的な処理はMoveEnemy関数で行うとする。
		MoveEnemy(ce->Part[i]);

		// 敵の描画：
		// 全てのパーツを一体化させて動かすために，
		// パーツの座標をボス座標からの相対位置として使う。
		// ボス全体を動かすにはce->Xとce->Yを変更する。
		// 具体的な処理はDrawEnemy関数で行うとする。
		DrawEnemy(ce->Part[i],
			ce->Part[i]->X+ce->X, ce->Part[i]->Y+ce->Y);

		// 敵の破壊：
		// 判定と破壊の具体的な処理は，
		// Destroyed，DeleteEnemyの各関数で行うとする。
		if (Destroyed(ce->Part[i])) {
			DeleteEnemy(ce->Part[i]);

			// ボス全体の破壊：
			// 破壊されたパーツが致命的だったときには，
			// ボス全体を破壊する。
			if (ce->Fatal[i]) DeleteEnemy(ce);
		}
	}
}


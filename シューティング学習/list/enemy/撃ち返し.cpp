#include <stdlib.h>

bool Destroyed();
void AimingBullet(float ex, float ey, float tx, float ty);
void Delete();

void Revenge(
	float rate,          // 撃ち返しの確率
	float ex, float ey,  // 敵の座標
	float tx, float ty   // 目標（自機）の座標
) {
	// 敵が破壊されたかどうかの判定：
	// 具体的な処理はDetroyed関数で行うとする。
	if (Destroyed()) {
	
		// 撃ち返し：
		// 乱数を使って一定確率で撃ち返す。
		// 撃ち返し弾は「狙い撃ち弾」と同じ。
		// 発射の具体的な処理はAimingBullet関数で行うとする。
		if (rand()<=rate*RAND_MAX) {
			AimingBullet(ex, ey, tx, ty);
		}
		
		// 敵を消す：
		// 具体的な処理はDelete関数で行うとする。
		Delete();
	}
}


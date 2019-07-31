void DeleteShot();
void SpecialShot();

void ReinforcedShot3(
	float sx0, float sy0,  // ショットの左上座標
	float sx1, float sy1,  // ショットの右下座標
	float cx0, float cy0,  // 味方の左上座標
	float cx1, float cy1   // 味方の右下座標
) {
	// ショットと味方との当たり判定処理：
	// 当たったときにはショットを消し，
	// 代わりに強いショットを出す。
	// 具体的な処理は，
	// DeleteShot，SpecialShotの各関数で行うとする。
	// ショットを消さずに，
	// ショットの強さだけを変える方法もある。
	if (cx0<sx1 && sx0<cx1 && cy0<sy1 && sy0<cy1) {
		DeleteShot();
		SpecialShot();
	}
}


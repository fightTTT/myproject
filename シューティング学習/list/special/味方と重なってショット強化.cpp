void SpecialShot();
void NormalShot();

void ReinforcedShot(
	float x0, float y0,    // 自機の左上座標
	float x1, float y1,    // 自機の右下座標
	float cx0, float cy0,  // 味方機の左上座標
	float cx1, float cy1,  // 味方機の右下座標
	bool button            // ショットボタンの状態
) {
	// 味方と接近しているかどうかの判定：
	// 接近している場合には強いショット，
	// していない場合には通常のショットを撃つ。
	// ショットを撃つ具体的な処理は，
	// SpecialShot，NormalShotの各関数で行うとする。
	if (button) {
		if (cx0<x1 && x0<cx1 && cy0<y1 && y0<cy1) {
			SpecialShot();
		} else {
			NormalShot();
		}
	}
}


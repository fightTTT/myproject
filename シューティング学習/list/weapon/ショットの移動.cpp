void DeleteShot();

void MoveShot(
	float& x0, float& y0,  // ショットの左上座標
	float& x1, float& y1,  // ショットの右下座標
	float vx, float vy,    // ショットの速度（X方向，Y方向）
	float sx0, float sy0,  // 画面枠の左上座標
	float sx1, float sy1   // 画面枠の右下座標
) {
	// ショットが画面外に出ていたら消す：
	// 具体的な処理はDeleteShot関数で行うとする。
	if (x1<=sx0 || sx1<=x0 || y1<=sy0 || sy1<=y0) DeleteShot();

	// ショットを移動する（座標を更新する）
	x0+=vx; y0+=vy;
	x1+=vx; y1+=vy;
}


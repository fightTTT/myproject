void MoveThrownShip(
	float& x0, float& y0,  // 機体の左上座標
	float& x1, float& y1,  // 機体の右下座標
	float& vx, float& vy,  // 機体の速度
	float sx0, float sy0,  // 移動可能範囲（画面枠）の左上座標
	float sx1, float sy1   // 移動可能範囲（画面枠）の右下座標
) {
	// 跳ね回る動きのための処理：
	// 画面枠の上下左右からはみ出しそうになったら，
	// 移動速度を逆にする。
	if (x0+vx<sx0 || sx1<=x1+vx) vx=-vx;
	if (y0+vy<sy0 || sy1<=y1+vy) vy=-vy;
	
	// 機体を移動させる
	x0+=vx; x1+=vx;
	y0+=vy; y1+=vy;
}


void MoveDroppingBullet(
	float& x, float& y,   // 弾の座標
	float accel,          // 加速度
	float& vx, float& vy  // 速度のX成分とY成分
) {
	// 速度を更新する：
	// X成分は変化させず，Y成分だけを変化させる。
	vy+=accel;

	// 座標を更新する
	x+=vx; y+=vy;
}

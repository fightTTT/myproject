void MoveAcceleratedBullet(
	float speed,          // 弾の速さ
	float accel,          // 加速度
	float& vx, float& vy  // 速度のX成分とY成分
) {
	// 速度を古い速さで割る
	if (speed!=0) {
		vx/=speed; vy/=speed;
	}

	// 速さを更新する
	speed+=accel;

	// 速度に新しい速さを掛ける
	vx*=speed; vy*=speed;
}


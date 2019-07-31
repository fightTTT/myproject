void InitAimingBulletDDA(
	int mx, int my,    // 自機の座標
	int ex, int ey,    // 敵の座標
	int& x, int& y,    // 弾の座標
	int& vx, int& vy,  // 弾の移動方向
	int& dx, int& dy,  // X方向とY方向の差分
	int& diff          // 誤差
) {
	// 弾の座標を設定する
	x=ex; y=ey;

	// 弾の移動方向(vx,vy)を求める：値は1または-1
	vx=mx>ex?1:-1;
	vy=my>ey?1:-1;

	// 目標に対するX方向とY方向の差分の絶対値(dx,dy)を求める
	dx=mx>=ex?mx-ex:ex-mx;
	dy=my>=ey?my-ey:ey-my;

	// 誤差diff：dx>=dyのときはdx/2，dx<dyのときはdy/2とする
	diff=dx>=dy?dx/2:dy/2;
}

void MoveAimingBulletDDA(
	int& x, int& y,  // 弾の座標
	int vx, int vy,  // 弾の移動方向
	int dx, int dy,  // X方向とY方向の差分
	int& diff,       // 誤差
	int speed        // 弾の速さ
) {
	// 移動距離のX方向が長いときの処理
	if (dx>=dy) {
		for (int i=0; i<speed; i++) {

			// X方向には毎回移動させる
			x+=vx;
			
			// Y方向には誤差が蓄積したときだけ移動させる
			diff+=dy;
			if (diff>=dx) {
				diff-=dx;
				y+=vy;
			}
		}
	} 

	// 移動距離のY方向が長いときの処理
	else {
		for (int i=0; i<speed; i++) {

			// Y方向には毎回移動させる
			y+=vy;

			// X方向には誤差が蓄積したときだけ移動させる
			diff+=dx;
			if (diff>=dy) {
				diff-=dy;
				x+=vx;
			}
		}
	}
}


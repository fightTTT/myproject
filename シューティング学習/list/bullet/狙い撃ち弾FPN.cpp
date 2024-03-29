void Draw(int x, int y);

void InitAimingBulletFP(
	int mx, int my,    // 自機の座標
	int ex, int ey,    // 敵の座標
	int& x, int& y,    // 弾の座標
	int& vx, int& vy,  // 弾の速度
	int speed          // 弾の速さ
) {
	// 弾の座標を設定する
	x=ex; y=ey;

	// 目標に対するX方向とY方向の差分の絶対値(dx,dy)を求める
	int dx=mx>=ex?mx-ex:ex-mx;
	int dy=my>=ey?my-ey:ey-my;

	// X方向とY方向の差分のうち長い方を距離dとする
	int d=dx>=dy?dx:dy;

	// 速度(vx,vy)を求める
	vx=(mx-ex)*speed/d;
	vy=(my-ey)*speed/d;
}

void MoveAimingBulletFP(
	int& x, int& y,  // 弾の座標
	int vx, int vy   // 弾の速度
) {
	// 弾の座標(x,y)に速度(vx,vy)を加える
	x+=vx;
	y+=vy;

	// 弾を描く：
	// 画面に弾を描くときには座標を(x>>8, y>>8)とする。
	// 弾を描く具体的な処理はDraw関数で行うとする。
	Draw(x>>8, y>>8);
}


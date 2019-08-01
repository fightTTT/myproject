void ScrollSpeed(
	int y,               // 自機のY座標
	int& svy,            // スクロールの速度（Y方向）
	int ymin, int ymax,  // 自機Y座標の最大値，最小値
	int smax, int smin   // スクロールの最大，最小スピード
) {
	svy=smin+(y-ymin)*(smax-smin)/(ymax-ymin);
}


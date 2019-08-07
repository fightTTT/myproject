void DrawBG(int x, int y);
void DrawMyShip(int x, int y);

void MixedScroll(
	int x, int y,  // 自機の背景上の座標
	int w,         // 自機の幅
	int sy,        // スクロール位置のY座標
	int svy,       // Y方向のスクロール速度
	int sw,        // 画面幅
	int bw         // 背景の幅
) {
	// 背景の描画：
	// スクロール位置を更新し，背景を描画する。
	// 描画の具体的な処理はDrawBG関数で行うとする。
	int sx=(bw-sw)*x/(bw-w);
	sy+=svy;
	DrawBG(sx, sy);
	
	// 自機の描画：
	// スクロール位置からの相対位置に表示する。
	// 描画の具体的な処理はDrawMyShip関数で行うとする。
	DrawMyShip(x-sx, y-sy);
}


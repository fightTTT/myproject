void DrawBG(int id);

void OverlaidScroll(
	int num_bg,           // 背景の数
	int sx[], int sy[],   // 各背景上の表示位置
	int svx[], int svy[]  // 各背景のスクロール速度
) {
	// 全背景の描画：
	// 各背景の表示位置を順に更新した後に表示する。
	// 表示の具体的な処理はDrawBG関数で行うとする。
	for (int i=0; i<num_bg; i++) {
		sx[i]+=svx[i];
		sy[i]+=svy[i];
		DrawBG(i);
	}
}


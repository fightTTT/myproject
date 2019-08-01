void DrawChip(int id, int x, int y);

// チップ数（X方向，Y方向）
#define XMAX 20
#define YMAX 400

// 背景の表示
void DrawBG(
	int sx, int sy,      // 画面左上に対応する背景上の位置
	int sw, int sh,      // 画面の大きさ
	int cw, int ch,      // チップの大きさ
	int map[YMAX][XMAX]  // 背景データ（チップ番号の配列）
) {
	// 描画するチップの範囲
	int x0=sx/cw, y0=sy/ch;                // 左上端のチップ
	int x1=(sx+sw-1)/cw, y1=(sy+sh-1)/ch;  // 右下端のチップ

	// チップの描画：
	// 各チップの描画はDrawChip関数で行うとする。
	for (int i=y0; i<=y1; i++) {
		for (int j=x0; j<=x1; j++) {
			DrawChip(map[i][j], j*cw-sx, i*ch-sy);
		}
	}
}


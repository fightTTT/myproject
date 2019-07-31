void DrawChip(int id, int x, int y);

// チップ数（X方向，Y方向）
#define XMAX 1000
#define YMAX 50

// 上下左右がつながった背景の表示
void DrawCirculatedBG(
	int sx, int sy,      // 画面左上に対応する背景上の位置
	int sw, int sh,      // 画面の大きさ
	int cw, int ch,      // チップの大きさ
	int map[XMAX][YMAX]  // 背景データ（チップ番号の配列）
) {
	// 描画するチップの範囲
	int x0=sx/cw, y0=sy/ch;    // 左上端のチップ
	int x1=(sx+sw-1)/cw%XMAX, 
		y1=(sy+sh-1)/ch%YMAX;  // 右下端のチップ

	// チップの描画：
	// 各チップの描画はDrawChip関数で行うとする。
	for (int i=x0; i!=x1+1; i=(i+1)%XMAX) {
		for (int j=y0; j!=y1+1; j=(j+1)%YMAX) {
			DrawChip(map[i][j], j*cw-sx, i*ch-sy);
		}
	}
}

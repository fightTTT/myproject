#include <math.h>

void DrawChip(int id, int x, int y);

// チップ数（X方向，Y方向）
#define XMAX 20
#define YMAX 400

// 背景の表示
void DrawBG(
	int sx, int sy,      // 画面の中心座標
	int sw, int sh,      // 画面の大きさ
	int cw, int ch,      // チップの大きさ
	int map[YMAX][XMAX]  // 背景データ（チップ番号の配列）
) {
	// 回転で画面内に入る背景の最大範囲を求める
	int w2=sw/2, h2=sh/2;            // 画面の幅と高さの1/2
	int r=(int)sqrt(w2*w2+h2*h2);    // 円の半径
	int x0=(sx-r)/cw, y0=(sy-r)/ch;  // 左上端のチップ
	int x1=(sx+r)/cw, y1=(sy+r)/ch;  // 右下端のチップ

	// チップの描画：
	// 各チップの描画はDrawChip関数で行うとする。
	for (int i=y0; i<=y1; i++) {
		for (int j=x0; j<=x1; j++) {
			DrawChip(map[i][j], j*cw-sx+sw/2, i*ch-sy+sh/2);
		}
	}
}


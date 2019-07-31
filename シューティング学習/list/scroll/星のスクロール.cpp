void DrawPixel(int x, int y, int color);

// 星の情報を保持する構造体
typedef struct {
	int X, Y;    // 座標
	int VX, VY;  // 速度
	int Color;     // 色
} STAR;

// 星のスクロール
void DrawStar(
	int num_star,   // 星の数
	STAR star[]    // 星の情報
) {
	// 星の移動と描画：
	// 描画の具体的な処理はDrawPixel関数で行うとする。
	for (int i=0; i<num_star; i++) {
		star[i].X+=star[i].VX;
		star[i].Y+=star[i].VY;
		DrawPixel(star[i].X, star[i].Y, star[i].Color);
	}
}


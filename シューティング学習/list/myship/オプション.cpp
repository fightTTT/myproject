void DrawOption(float x, float y);

// オプションの初期化
void InitOption(
	float x, float y,        // 自機の座標（X方向，Y方向）
	float ox[], float oy[],  // 自機の古い座標（配列）
	int length               // 古い座標の個数（配列の長さ）
) {
	// 配列の全要素を自機の座標で初期化する
	for (int i=0; i<length; i++) {
		ox[i]=x; oy[i]=y;
	}
}

// オプションの移動
void MoveOption(
	float x, float y,        // 自機の座標（X方向，Y方向）
	float ox[], float oy[],  // 自機の古い座標（配列）
	int length,              // 古い座標の数（配列の長さ）
	int& index,              // 座標の保存位置（配列上の位置）
	int opt_count,           // オプションの個数
	int opt_interval         // オプションの間隔（配列上の間隔）
) {
	// オプションを描く：
	// DrawOptionはオプションを描く関数とする
	for (int c=0, i=index; c<opt_count; c++) {
		i=(i-opt_interval+length)%length;
		DrawOption(ox[i], oy[i]);
	}
	
	// 自機の座標を保存し，座標の保存位置を更新する
	ox[index]=x;
	oy[index]=y;
	index=(index+1)%length;
}


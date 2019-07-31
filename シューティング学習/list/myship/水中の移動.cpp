void WaveEffect();

void Underwater1(
	float& x, float& y,  // 自機の座標
	float vx, float vy,  // 自機の速度
	float h              // 水面の高さ
) {
	// 空中の場合：
	// 通常の速度で移動する。
	if (y<h) {
		x+=vx; y+=vy;
	}

	// 水中の場合：
	// 速度を遅くする。ここでは空中の半分とした。
	else {
		x+=vx/2; y+=vy/2;
	}
}

void Underwater2(
	float& x, float& y,        // 自機の座標
	float x0, float y0,        // 自機の左上座標
	float x1, float y1,        // 自機の右下座標
	float vx, float vy,        // 自機の速度
	float wx0[], float wy0[],  // 水の当たり判定
	float wx1[], float wy1[],  // （左上座標，右下座標）
	int num_water              // 水の当たり判定の数
) {
	// 自機が水中にいるかどうかを調べる
	int i;
	for (i=0; i<num_water; i++) {
		if (wx0[i]<=x0 && x1<=wx1[i] && 
			wy0[i]<=y0 && y1<=wy1[i]) break;
	}
	
	// 自機が水中にいる場合：
	// 速度を遅くする。ここでは空中の半分とした。
	if (i<num_water) {
		x+=vx/2; y+=vy/2;
	}
	
	// 自機が水中にはいない場合：
	// 通常の速度で移動する
	else {
		x+=vx; y+=vy;
		
		// 自機が水面に接触しているかどうかを調べる
		for (i=0; i<num_water; i++) {
			if (wx0[i]<x1 && x0<wx1[i] && 
				wy0[i]<y1 && y0<wy1[i]) break;
		}

		// 自機が水面に接触している場合：
		// 波しぶきなどのエフェクトを表示する。
		// 具体的な処理はWaveEffect関数で行うとする。
		if (i<num_water) WaveEffect();
	}
}


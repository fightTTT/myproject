void GrazeBullet(
	float gx0, float gy0,    // かすり判定の左上座標
	float gx1, float gy1,    // かすり判定の右下座標
	int num_bullet,          // 弾の数
	float x0[], float y0[],  // 弾の当たり判定の左上座標
	float x1[], float y1[],  // 弾の当たり判定の右下座標
	bool grazing[],          // 弾がかすっているかどうか
	int time[],              // かすり時間
	int& power               // 自機のパワー
	                         // （経験値，得点倍率など）
) {
	// 全ての弾について処理を行う
	for (int i=0; i<num_bullet; i++) {

		// 通常状態：
		// 当たり判定処理を行い，弾が自機にかすったら，
		// かすり状態にする。
		// かすり状態の残り時間を設定し，自機のパワーを増やす。
		if (!grazing[i]) {
			if (gx0<x1[i] && x0[i]<gx1 && 
				gy0<y1[i] && y0[i]<gy1) {
				grazing[i]=true;
				time[i]=20;
				power++;
			}
		}
		
		// かすり状態：
		// かすり状態の残り時間を減らし，
		// 時間が0になったら通常状態に戻る。
		// この処理をなくせば，1つの弾に1度しかかすれなくなる。
		else {
			if (time[i]==0) grazing[i]=false; else time[i]--;
		}
	}
	
}


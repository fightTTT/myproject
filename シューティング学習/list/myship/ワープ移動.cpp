void Warp(
	float& x, float& y,    // 自機の座標
	float speed,           // 自機の移動速度
	float warp_dist,       // ワープの移動距離
	bool up, bool down,    // スティック入力（上下）
	bool left, bool right  // スティック入力（左右）
) {
	static bool 
		up0=false, down0=false,     // 前回のスティック入力
		left0=false, right0=false,  // （上下，左右）
		released=true;              // 無入力状態にしたかどうか
	static int time=0;              // 入力の制限時間

	// スティックが入力されたとき
	if (up || down || left || right) {
		
		// ワープする場合：
		// 無入力をはさんで，かつ制限時間内に，
		// 前回と同じ方向が入力されたとき。
		if (released && time>0 &&
			up==up0 && down==down0 &&
			left==left0 && right==right0
		) {
			if (up   ) y-=warp_dist;
			if (down ) y+=warp_dist;
			if (left ) x-=warp_dist;
			if (right) x+=warp_dist;
		}
		
		// ワープしない場合：
		// 無入力をはさんでいないか，制限時間切れか，
		// 前回と異なる方向が入力されたとき。
		// 方向を記録し，制限時間を設定する。
		else {
			up0=up; down0=down;
			left0=left; right0=right;
			time=10;
			
			// 普通に移動する
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
		}

		released=false;
	}
	
	// スティックが無入力状態のとき
	else released=true;
	
	// 時間を減らす
	if (time>0) time--;
}


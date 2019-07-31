void SpeedControlByButton(
	float& speed,     // スピード
	float accel,      // スピードアップの度合い
	float max_speed,  // 最高速
	float min_speed,  // 最低速
	bool button       // 速度調節ボタンの入力
) {
	// 前回のボタンの状態
	static bool prev_button=false;
	
	// ボタンを一度離して押した場合：
	// 速度調節を行う。
	if (!prev_button && button) {
		if (speed>=max_speed) speed=min_speed;
		else speed+=accel;
	}
	
	// ボタンの状態を記録する
	prev_button=button;
}

void SpeedControlByItem(
	float& speed,          // スピード
	float max_speed,       // 最高速
	float min_speed,       // 最低速
	float x0, float y0,    // 拾い判定の左上座標
	float x1, float y1,    // 拾い判定の右下座標
	float ix0, float iy0,  // アイテムの当たり判定の左上座標
	float ix1, float iy1,  // アイテムの当たり判定の右下座標
	float accel            // スピードアップ・ダウンの度合い
) {
	// アイテムを拾ったときの処理：
	// 当たり判定処理を行い，当たったときには，
	// スピードアップまたはスピードダウンを行う。
	if (ix0<x1 && x0<ix1 && iy0<y1 && y0<iy1) {
		speed+=accel;
		
		// 以下のようにすると，
		// スピードダウンを1個拾っただけで，
		// スピードが最低になるようにできる。
		// if (accel<0) speed=min_speed;
		
		// スピードが最高速や最低速を超えたら補正する
		if (speed>max_speed) speed=max_speed;
		if (speed<min_speed) speed=min_speed;
	}
}



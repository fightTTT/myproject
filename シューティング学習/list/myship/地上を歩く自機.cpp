// 自機の状態（歩行，上昇，下降）
typedef enum {
	WALKING, JUMP_UP, JUMP_DOWN
} MYSHIP_STATE;

// 自機の動き
void Walk(
	float& x, float& y,     // 自機の座標
	float speed,            // 自機の速さ
	bool left, bool right,  // スティック入力（左右）
	bool jump_button        // ジャンプボタンの入力
) {
	static MYSHIP_STATE state=WALKING;  // 自機の状態
	static int time;                    // ジャンプの時間
	
	// 左右への移動
	if (left ) x-=speed;
	if (right) x+=speed;

	// 状態によって分岐する
	switch (state) {

		// 歩行：
		// ジャンプボタンを押したら上昇状態に移行する。
		case WALKING:
			if (jump_button) {
				state=JUMP_UP;
				time=40;
			}
			break;
		
		// 上昇：
		// 一定時間上昇したら下降状態に移行する。
		case JUMP_UP:
			y-=speed;
			if (time==0) {
				state=JUMP_DOWN;
				time=40;
			} else time--;
			break;
		
		// 下降：
		// 一定時間下降したら歩行状態に戻る。
		case JUMP_DOWN:
			y+=speed;
			if (time==0) state=WALKING; else time--;
			break;
	}
}

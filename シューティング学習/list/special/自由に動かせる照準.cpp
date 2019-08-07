// 状態（通常，照準，攻撃）
typedef enum {
	NORMAL, SIGHT, ATTACK
} STATE_TYPE;

// 自機と照準を動かす
void MoveSight1(
	float& x, float& y,     // 自機の座標
	float& sx, float& sy,   // 照準の座標
	float speed,            // 自機の移動の速さ
	float sight_speed,      // 照準の移動の速さ
	bool up, bool down,     // スティック入力（上下）
	bool left, bool right,  // スティック入力（左右）
	bool button             // 照準ボタン入力
) {
	static int state=NORMAL;  // 状態（通常から開始）
	static int time;          // 攻撃時間
	
	// 状態に応じて分岐する
	switch (state) {
	
		// 通常状態：
		// 自機を移動し，
		// ボタンが押されたら照準を出して，照準状態に移る。
		case NORMAL:
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
			if (button) {
				state=SIGHT;
				sx=x; sy=y;
			}
			break;
		
		// 照準状態：
		// 照準を移動し，ボタンが離されたら攻撃状態に移る。
		case SIGHT:
			if (up   ) sy-=sight_speed;
			if (down ) sy+=sight_speed;
			if (left ) sx-=sight_speed;
			if (right) sx+=sight_speed;
			if (!button) {
				state=ATTACK;
				time=100;
			}
			break;
		
		// 攻撃状態：
		// 自機を移動し，一定時間が経ったら通常状態に戻る。
		case ATTACK:
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
			if (time==0) state=NORMAL;
			time--;
			break;
	}
}


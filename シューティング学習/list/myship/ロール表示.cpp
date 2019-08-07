typedef enum {
	LEFT_BIG_ROLL, LEFT_SMALL_ROLL,
	CENTER,
	RIGHT_SMALL_ROLL, RIGHT_BIG_ROLL
} ROLL;

void Draw(ROLL roll);

void RollMyShip(
	int& roll,             // ロールの角度
	bool left, bool right  // 左右方向へのスティック入力
) {
	// スティックで左を入力した場合：
	// -20<rollならばrollを-1する。
	if (left && -20<roll) roll--;

	// スティックで右を入力した場合：
	// roll<20ならばrollを+1する。
	if (right && roll<20) roll++;

	// スティックで左も右も入力していない場合：
	// rollが0に近づくようにする。
	if (!left && !right) {
		if (roll<0) roll++; else
		if (0<roll) roll--;
	}

	// rollの値に応じて異なるパターンを表示する：
	// パターン表示の具体的な処理は関数Drawの中で行うとする。
	if (-20<=roll && roll<-15) Draw(LEFT_BIG_ROLL);    else
	if (-15<=roll && roll< -5) Draw(LEFT_SMALL_ROLL);  else
	if ( -5<=roll && roll<= 5) Draw(CENTER);           else
	if (  5< roll && roll<=15) Draw(RIGHT_SMALL_ROLL); else
	if ( 15< roll && roll<=20) Draw(RIGHT_BIG_ROLL);
}


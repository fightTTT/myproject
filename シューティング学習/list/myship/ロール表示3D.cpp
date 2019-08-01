void Draw(int roll);

void RollMyShip3D(
	int& roll,             // ロールの角度
	bool left, bool right  // 左右方向へのスティック入力
) {
	// スティックで左を入力した場合：
	// -60<rollならばrollを-3する。
	if (left && -60<roll) roll-=3;

	// スティックで右を入力した場合：
	// roll<60ならばrollを+3する。
	if (right && roll<60) roll+=3;

	// スティックで左も右も入力していない場合：
	// rollが0に近づくようにする。
	if (!left && !right) {
		if (roll<0) roll+=3; else
		if (0<roll) roll-=3;
	}

	// rollの値に応じて自機を回転させて表示する：
	// 表示の具体的な処理はDraw関数で行うとする。
	Draw(roll);
}


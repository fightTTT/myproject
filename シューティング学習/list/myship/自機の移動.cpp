void MoveMyShip(
	float& x, float& y,    // 自機の座標（X方向，Y方向）
	float speed,           // 自機の速さ
	bool up, bool down,    // 上下方向へのスティック入力
	bool left, bool right  // 左右方向へのスティック入力
) {
	if (up   ) y-=speed;
	if (down ) y+=speed;
	if (left ) x-=speed;
	if (right) x+=speed;
}


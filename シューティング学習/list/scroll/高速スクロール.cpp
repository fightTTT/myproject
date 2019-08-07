void ScrollForce(
	int& x, int& y,   // 自機の座標
	int vx, int vy,   // 自機の速度
	int svx, int svy  // スクロールの速度
) {
	x+=vx+svx/2;
	y+=vy+svy/2;
}


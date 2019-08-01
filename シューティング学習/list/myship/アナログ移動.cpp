void MoveByAnalog(
	float& x, float& y,    // 自機の座標（X方向，Y方向）
	float speed,           // 自機の最高速度
	int jx, int jy,        // スティックの入力値（X方向，Y方向）
	int range, int margin  // 入力値の範囲（最大値），マージン
) {
	// X方向に関する移動
	if (jx<=-range+margin) x-=speed; else
	if (+range-margin<=jx) x+=speed; else
	if (jx<-margin) x+=speed*(jx+margin)/(range-margin*2); else
	if (+margin<jx) x+=speed*(jx-margin)/(range-margin*2);
	
	// Y方向に関する移動
	if (jy<=-range+margin) y-=speed; else
	if (+range-margin<=jy) y+=speed; else
	if (jy<-margin) y+=speed*(jy+margin)/(range-margin*2); else
	if (+margin<jy) y+=speed*(jy-margin)/(range-margin*2);
}


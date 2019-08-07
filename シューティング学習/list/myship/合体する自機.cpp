bool EnemyDestroyed();
bool Catched();

// 味方の状態（捕捉，浮遊，合体）
typedef enum {
	CAPTURED, FLOATING, DOCKED
} DOCKING_STATE;

// 合体に関する処理
void Docking(
	float& cx, float& cy,  // 味方の座標
	float ex, float ey,    // 敵の座標
	float mx, float my,    // 自機の座標
	DOCKING_STATE& state   // 味方の状態
) {
	// 味方の状態によって分岐する
	switch (state) {
		
		// 捕捉：
		// 敵と一緒に動く。
		// 敵が破壊されたら浮遊状態に移行する。
		// 敵の破壊判定処理はEnemyDestroyed関数で行うとする。
		case CAPTURED:
			cx=ex; cy=ey;
			if (EnemyDestroyed()) state=FLOATING;
			break;
		
		// 浮遊：
		// 自由に動く。
		// ここでは画面下方向に直進するとする。
		// 自機に接触したら合体状態に移行する。
		// 接触判定処理はCatched関数で行うとする。
		case FLOATING:
			cy++;
			if (Catched()) state=DOCKED;
			break;
		
		// 合体：
		// 自機と一緒に動く。
		case DOCKED:
			cx=mx; cy=my;
			break;
	}
}


bool CaptureAttack();
void NormalAttack();
bool Destroyed();
void ReturnMyShip();
void Delete();

// 敵の状態：
// 通常，捕捉
typedef enum {
	NORMAL, CAPTURED
} CAPTOR_STATE;

// 自機をとらえる敵の動き
void Captor(
	bool capture  // 今回，捕捉攻撃をするかどうか
) {
	static int state=NORMAL;  // 敵の状態
	
	// 状態によって分岐する
	switch (state) {
		
		// 通常状態：
		// 通常攻撃または捕捉攻撃を行う。
		// 捕捉攻撃が成功したら捕捉状態に移る。
		// 攻撃の具体的な処理は，CaptureAttack，
		// NormalAttackの各関数で行うとする。
		case NORMAL:
			if (capture) {
				if (CaptureAttack()) state=CAPTURED;
			} else {
				NormalAttack();
			}
			break;
		
		// 捕捉状態：
		// 通常攻撃を行う。
		// 破壊されたら自機を返した後に消滅する。
		// 判定などの具体的な処理は，Destroyed，
		// ReturnMyShip，Deleteの各関数で行うとする。
		case CAPTURED:
			NormalAttack();
			if (Destroyed()) {
				ReturnMyShip();
				Delete();
			}
			break;
	}
}


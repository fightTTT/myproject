// ボスの状態：
// 攻撃0，攻撃1，攻撃2，待機
typedef enum {
	ATTACK0, ATTACK1, ATTACK2, WAIT
} BOSS_STATE;

void Attack0();
void Attack1();
void Attack2();

// 各状態の制限時間
int Time[]={30, 40, 25, 20};

// ボスの行動
void MoveBoss(
	BOSS_STATE& state,  // 現在の状態
	int& timer           // タイマー
) {
	// 攻撃：
	// 状態に応じた攻撃を行う。待機のときには何もしない。
	// 攻撃の具体的な処理は，
	// Attack0，Attack1，Attack2の各関数で行うとする。
	switch (state) {
		case ATTACK0: Attack0(); break;
		case ATTACK1: Attack1(); break;
		case ATTACK2: Attack2(); break;
	}
	
	// 状態遷移：
	// タイマーを加算し，
	// 各状態の制限時間を超えたら次の状態に移行する。
	timer++;
	if (timer>Time[state]) {
		state=(BOSS_STATE)((state+1)%4);
		timer=0;
	}
}


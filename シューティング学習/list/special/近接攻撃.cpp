void DamageEnemy(int id);
void DrawPunch();

// 近接攻撃に関する処理
void Punch(
	bool button,               // ボタンの状態（押したときtrue）
	float px0, float py0,      // 近接攻撃の左上座標
	float px1, float py1,      // 近接攻撃の右下座標
	float ex0[], float ey0[],  // 敵の左上座標
	float ex1[], float ey1[],  // 敵の右下座標
	int num_enemy              // 敵の数
) {
	static bool punching=false;  // 近接攻撃中かどうか
	static int punch_time;       // 近接攻撃を出している時間
	
	// 近接攻撃の開始：
	// 近接攻撃中ではなく，ボタンが押されていたら，
	// 近接攻撃を出す。
	if (!punching && button) {
		punching=true;
		punch_time=30;
	}
	
	// 近接攻撃中の処理
	if (punching) {

		// 敵との当たり判定処理：
		// ダメージを与える具体的な処理は，
		// DamageEnemy関数で行うとする。
		for (int i=0; i<num_enemy; i++) {
			if (ex0[i]<px1 && px0<ex1[i] && 
				ey0[i]<py1 && py0<ey1[i]) {
				DamageEnemy(i);
			}
		}

		// 近接攻撃の表示：
		// 表示の具体的な処理はDrawPunch関数で行うとする。
		DrawPunch();

		// 近接攻撃の持続と終了：
		// 持続時間を過ぎたら近接攻撃を引っ込める。
		if (punch_time==0) punching=false; else punch_time--;
	}
}


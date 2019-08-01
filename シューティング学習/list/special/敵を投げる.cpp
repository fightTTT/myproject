void DeleteEnemy(int id);
void CreateExplosion(float x, float y);

// アームの状態：
// 待機，伸びている途中，伸びきった，縮んでいる途中。
typedef enum {
	READY, EXTENDING, EXTENDED, SHRINKING
} STATE_TYPE;

// アームの動き
void MoveArm(
	bool button  // アームを伸ばすボタンの状態
) {
	static STATE_TYPE state=READY;  // アームの状態
	static int length;              // アームの長さ
	static int max_length=20;       // アームの最大長
	static int time;                // 時間待ち用
	
	// アームの状態によって処理を変える
	switch (state) {
		
		// 待機：
		// ボタンが押されたらアームを伸ばす。
		case READY:
			if (button) {
				state=EXTENDING;
				length=0;
			}
			break;
		
		// 伸びている途中：
		// アームを伸ばし，
		// 最大長に達したら伸びきった状態に移る。
		case EXTENDING:
			if (length<max_length) {
				length++;
			} else {
				state=EXTENDED;
				time=10;
			}
			break;
		
		// 伸びきった：
		// 一定時間が経過したら縮ませる。
		case EXTENDED:
			if (time>0) {
				time--;
			} else {
				state=SHRINKING;
			}
			break;
		
		// 縮んでいる途中：
		// 長さが0になったら待機状態に戻る。
		case SHRINKING:
			if (length>0) {
				length--;
			} else {
				state=READY;
			}
			break;
	}
}

void MoveThrownEnemy(
	float& x0, float& y0,      // 投げつけられた敵の左上座標
	float& x1, float& y1,      // 投げつけられた敵の右下座標
	float vx, float vy,        // 投げつけられた敵の速度
	float ex0[], float ey0[],  // 他の敵の左上座標
	float ex1[], float ey1[],  // 他の敵の右下座標
	int num_enemy              // 他の敵の数
) {
	// 敵との当たり判定処理：
	// 投げつけられた敵と，他の全ての敵との間で
	// 当たり判定処理を行う。
	// 衝突したら，投げつけられた敵を消し，
	// 代わりに爆風を出す。
	// 消滅と出現の具体的な処理は，
	// DeleteEnemy，CreateExplosionの各関数で行うとする。
	int i;
	for (i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DeleteEnemy(i);
			CreateExplosion(x0, y0);
		}
	}
	
	// どの敵にもぶつからなかった場合：
	// 投げつけられた敵を動かす。
	if (i==num_enemy) {
		x0+=vx; y0+=vy;
		x1+=vx; y1+=vy;
	}
}



void MoveEnemy(int id);
void DeleteEnemy(int id);
void DrawEnemy(float x, float y, float alpha);

// 敵の状態を表す定数：
// 準備（出現前），出現，活動，消失
typedef enum {
	READY, APPEAR, ACT, DISAPPEAR
} STATE_TYPE;

// 出現と消失にかかる時間，活動時間
#define TIME 30
#define ACT_TIME 180

// 空中に現れる敵の処理
void EmergingEnemy(
	int num_enemy,           // 敵の数
	STATE_TYPE state[],      // 敵の状態
	float ex[], float ey[],  // 敵の座標
	float alpha[],           // アルファ値
	int timer[]              // タイマー
) {
	// 全ての敵に関するループ
	for (int i=0; i<num_enemy; i++) {
		
		// 状態に応じて分岐
		switch (state[i]) {
			
			// 準備（出現前）：
			// アルファ値とタイマーを初期化して，
			// 出現状態に移行する。
			case READY:
				state[i]=APPEAR;
				alpha[i]=0;
				timer[i]=TIME;
				break;
			
			// 出現：
			// アルファ値をだんだん大きくする。
			// タイマーが0になったら活動状態に移行する。
			case APPEAR:
				alpha[i]=(float)(TIME-timer[i])/TIME;
				timer[i]--;
				if (timer[i]==0) {
					state[i]=ACT;
					timer[i]=ACT_TIME;
				}
				break;
			
			// 活動：
			// 移動や攻撃を行う。
			// タイマーが0になったら消失状態に移行する。
			// 移動や攻撃の具体的な処理は，
			// MoveEnemy関数で行うとする。
			case ACT:
				MoveEnemy(i);
				timer[i]--;
				if (timer[i]==0) {
					state[i]=DISAPPEAR;
					timer[i]=TIME;
				}
				break;
			
			// 消失：
			// アルファ値をだんだん小さくする。
			// タイマーが0になったら敵を消す。
			// 敵を消す具体的な処理は，
			// DeleteEnemy関数で行うとする。
			case DISAPPEAR:
				alpha[i]=(float)timer[i]/TIME;
				timer[i]--;
				if (timer[i]==0) {
					DeleteEnemy(i);
				}
				break;
		}
		
		// 敵の表示：
		// アルファ値に基づいてアルファ合成表示を行う。
		DrawEnemy(ex[i], ey[i], alpha[i]);
	}
}

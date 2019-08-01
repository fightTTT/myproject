bool PickItem();
void PowerUp(int id);

// パワーアップの種類
typedef enum {
	NONE,  // カーソルがない状態
	SPEED, MISSILE, DOUBLE, 
	LASER, OPTION, BARRIER, 
	END    // ゲージの右端を示す
} POWER_UP_TYPE;

// ゲージを使ったパワーアップ
void PowerUpGauge(
	bool power_up_button  // パワーアップボタンの入力
) {
	static POWER_UP_TYPE cursor=NONE;  // カーソルの位置
	
	// アイテムを拾ったときの処理：
	// アイテムを拾ったら，カーソルを1つ右に動かす。
	// 右端まで動いたら左端に戻す。
	// 拾い判定処理はPickItem関数で行うとする。
	if (PickItem()) {
		cursor++;
		if (cursor==END) cursor=SPEED;
	}
	
	// パワーアップの処理：
	// ボタンが押されたら，
	// カーソルが指しているパワーアップを行う。
	// 具体的な処理はPowerUp関数で行うとする。
	if (power_up_button) {
		PowerUp(cursor);
	}
}


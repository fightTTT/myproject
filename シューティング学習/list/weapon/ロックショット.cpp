void Shot();
void AimingShot(int id);
void DirectedShot(int dir);

void LockShot(
	bool button,     // ボタンの状態（押されたときtrue）
	int min_power,   // 溜めパワーの最小値
	int max_gauge,   // 連射ゲージの最大値
	int enemy_id,    // ロックショットが追尾している敵のID
	                 // （追尾していないときには負の値）
	float front_dir  // 自機の正面に相当する方向
) {
	// 溜めパワー，連射ゲージ
	static int power=0, gauge=0;

	// ボタンを押している場合
	if (button) {
		
		// 溜めパワー不足の場合：
		// 溜めパワーを増やし，連射ゲージを最大にして，
		// 弾を撃つ。具体的な処理はShot関数で行うとする。
		if (power<min_power) {
			power++;
			gauge=max_gauge;
			Shot();
		}
	
		// 溜めパワー十分の場合：
		// 連射ゲージを0にして，ロックショットを撃つ。
		else {
			gauge=0;
			
			// ロックショットを撃つ：
			// 敵を追尾しているときは敵を狙い撃ちする。
			// （「自機に向かって飛ぶ弾」と同様）
			// 敵を追尾していないときは自機の正面に弾を撃つ。
			// （「自由な方向に飛ぶ弾」と同様）
			// それぞれ具体的な処理はAimingShot関数と
			// DirectedShot関数で行うとする。
			if (enemy_id>=0) {
				AimingShot(enemy_id);
			} else {
				DirectedShot(front_dir);
			}
		}
	}
	
	// ボタンを離している場合：
	else {
		
		// 連射ゲージ>0の場合：
		// 普通の弾を撃ち，連射ゲージを-1する。
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// 溜めパワーを0にする
		power=0;
	}
}


void Shot();
void Laser();

void ShotAndLaser(
	bool button,    // ボタンの状態（押されたときtrue）
	int min_power,  // 溜めパワーの最小値
	int max_gauge   // 連射ゲージの最大値
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
		// 連射ゲージを0にして，レーザーを撃つ。
		// 具体的な処理はLaser関数で行うとする。
		else {
			gauge=0;
			Laser();
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


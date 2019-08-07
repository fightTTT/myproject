void PowerEffect();
void Shot();
void BigShot(int power);
void MaxShot();

void SemiAutoShot(
	bool button,    // ボタンの状態（押されたときtrue）
	int min_power,  // 溜めパワーの最小値
	int max_power,  // 溜めパワーの最大値
	int max_gauge   // 連射ゲージの最大値
) {
	// 溜めパワー，連射ゲージ
	static int power=0, gauge=0;

	// ボタンを押している場合
	if (button) {
		
		// 溜めパワー不足の場合：
		// 通常の弾を撃つ。
		// 具体的な処理はShot関数で行うとする。
		if (power<min_power) Shot();
	
		// 溜めパワー十分の場合：
		// 溜め状態の表示をする。
		// 具体的な処理はPowerEffect関数で行うとする。
		else PowerEffect();
	
		// 溜めパワーを増やし，連射ゲージを最大にする
		if (power<max_power) power++;
		gauge=max_gauge;
	}
	
	// ボタンを離している場合：
	else {
		
		// 溜めパワー十分の場合：
		// 溜め撃ち弾を撃つ：
		// 最大パワーのときは特別な弾を撃つ。
		// 具体的な処理はMaxShot関数とBigShot関数で行うとする。
		if (min_power<=power) {
			if (power==max_power) MaxShot(); 
				else BigShot(power);
			gauge=0;
		}
		
		// 連射ゲージ>0の場合：
		// 通常の弾を撃ち，連射ゲージを-1する。
		// 具体的な処理はShot関数で行うとする。
		if (gauge>0) {
			Shot();
			gauge--;
		}

		// 溜めパワーを0にする
		power=0;
	}
}


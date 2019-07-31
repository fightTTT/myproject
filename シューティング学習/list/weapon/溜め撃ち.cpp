void BigShot(int power);
void MaxShot();

void PowerShot(
	bool button,    // ボタンの状態（押されたときtrue）
	int min_power,  // 弾が出る最小のパワー
	int max_power   // 最大のパワー
) {
	// 溜めパワー
	static int power=0;

	// ボタンを押している場合：
	// 溜めパワーを増やす。
	if (button && power<max_power) power++;
	
	// ボタンを離している場合：
	// 溜めパワー>0ならば弾を撃ち，溜めパワーを0に戻す。
	if (!button && power>0) {
		
		// 最大パワーのとき：
		// 特別な弾を撃つ。
		// 具体的な処理はMaxShot関数で行うとする。
		if (power==max_power) MaxShot(); else
		
		// 最小パワー以上，最大パワー未満のとき：
		// 溜めパワーに応じた強さの溜め撃ち弾を撃つ。
		// 具体的な処理はBigShot関数で行うとする。
		if (min_power<=power) BigShot(power);
		
		// 溜めパワーを0に戻す
		power=0;

	}
}

void PowerShotReleased(
	bool button,    // ボタンの状態（押されたときtrue）
	int min_power,  // 弾が出る最小のパワー
	int max_power   // 最大のパワー
) {
	// 溜めパワー
	static int power=0;

	// ボタンを離している場合：
	// 溜めパワーを増やす。
	if (!button && power<max_power) power++;
	
	// ボタンを押している場合：
	// 溜めパワー>0ならば弾を撃ち，溜めパワーを0に戻す。
	if (button && power>0) {
		
		// 最大パワーのとき：
		// 特別な弾を撃つ。
		// 具体的な処理はMaxShot関数で行うとする。
		if (power==max_power) MaxShot(); else
		
		// 最小パワー以上，最大パワー未満のとき：
		// 溜めパワーに応じた強さの溜め撃ち弾を撃つ。
		// 具体的な処理はBigShot関数で行うとする。
		if (min_power<=power) BigShot(power);
		
		// 溜めパワーを0に戻す
		power=0;
	}
}


void Shot();

void BasicShot(
	bool button  // 今回のボタンの状態（押されたときtrue）
) {
	// 前回のボタンの状態（押されたときtrue）
	static bool prev_button=false;
	
	// ショットの発射：
	// 前回ボタンが押されておらず，今回押されているときだけ，
	// ショットを発射する。
	// 発射の詳細な処理はShot関数で行うものとする。
	if (!prev_button && button) Shot();
	
	// 今回のボタンの状態を保存する
	prev_button=button;
}


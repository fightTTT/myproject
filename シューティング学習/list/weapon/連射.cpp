void Shot();

void AutoShot(
	bool button  // ボタンの状態（押されたときtrue）
) {
	// ショットの発射：
	// ボタンが押されていたらショットを発射する。
	// 発射の詳細な処理はShot関数で行うものとする。
	if (button) Shot();
}


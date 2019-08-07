void Shot(bool color);
bool HitBullet(int id);
void DeleteBullet(int id);
void Miss();

void SwitchColors(
	bool color_button,   // 色切り替えボタンの状態
	bool shot_button,    // ショットボタンの状態
	int num_bullet,      // 弾の数
	bool bullet_color[]  // 弾の色
) {
	static bool prev_col_button=false;  // 前回のボタンの状態
	static bool color=true;             // 自機の色
	static int energy=0;                // エネルギー
	
	// 色を切り替える
	if (!prev_col_button && color_button) color=~color;
	prev_col_button=color_button;
	
	// ショットを撃つ：
	// 自機と同じ色のショットを撃つ。
	// ショットの具体的な処理はShot関数で行うとする。
	if (shot_button) Shot(color);
	
	// 弾との当たり判定処理：
	// 判定の具体的な処理はHitBullet関数で行うとする。
	for (int i=0; i<num_bullet; i++) {
		if (HitBullet(i)) {
			
			// 同じ色ならば吸収：
			// 弾を消し，エネルギーを増やす。
			// 消去の具体的な処理はDeleteBullet関数で行うとする。
			if (color==bullet_color[i]) {
				DeleteBullet(i);
				energy++;
			}
			
			// 異なる色ならばミス：
			// ミスの具体的な処理はMiss関数で行うとする。
			else {
				Miss();
			}
		}
	}
}


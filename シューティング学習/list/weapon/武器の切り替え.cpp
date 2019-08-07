void DrawIcon(int id);
void FocusIcon(int id);

// 武器の数
#define MAX_WEAPONS 5

// 武器を切り替える処理
void SelectWeapon(
	bool button  // ボタンの状態（押したときtrue）
) {
	static int weapon_id=0;         // 現在選択中の武器の番号
	static bool prev_button=false;  // 前回のボタンの状態
	
	// 武器を切り替える：
	// 前回ボタンを押しておらず，今回押していたら，
	// 武器の切り替えを行う。
	if (!prev_button && button) {
		weapon_id=(weapon_id+1)%MAX_WEAPONS;
	}
	
	// 武器のアイコンを表示する：
	// 全アイコンを表示し，選択中のアイコンは目立たせる。
	// 表示の具体的な処理はDrawIcon関数とFocusIcon関数で
	// 行うとする。
	for (int i=0; i<MAX_WEAPONS; i++) DrawIcon(i);
	FocusIcon(weapon_id);

	// 今回のボタンの状態を保存する
	prev_button=button;
}



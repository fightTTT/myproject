void Walk();
void Fly();

// 自機の形態（歩行，飛行）
typedef enum {
	WALKING, FLYING
} MYSHIP_FORM;

// 自機の変形
void Transform(
	bool button  // 変形ボタンの入力
) {
	static MYSHIP_FORM formation=WALKING;  // 自機の形態
	static bool prev_button=false;         // 前回のボタン入力
	
	// 変形：
	// 変形ボタンが押されたら変形する。
	if (!prev_button && button) {
		if (formation==WALKING) formation=FLYING;
			else formation=WALKING;
	}
	prev_button=button;
	
	// 形態によって動きを変える：
	// 具体的な処理はWalk，Flyの各関数で行うとする。
	if (formation==WALKING) Walk(); else Fly();
}


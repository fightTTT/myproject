void NormalAttack();
void SpecialAttack();

void ItemSpecialAttack(
	float x0, float y0,        // 自機の左上座標
	float x1, float y1,        // 自機の右下座標
	float ix0[], float iy0[],  // アイテムの左上座標
	float ix1[], float iy1[],  // アイテムの左上座標
	int num_item               // アイテムの数
) {
	static bool special=false;  // 今の状態が特殊ならばtrue
	static int time;            // 特殊攻撃の残り時間
	
	// 通常状態のとき
	if (!special) {

		// 通常攻撃を行う：
		// 具体的な処理はNormalAttack関数で行うとする。
		NormalAttack();
		
		// アイテムを拾ったかどうかの判定：
		// 拾ったら特殊状態に移り，残り時間を設定する。
		for (int i=0; i<num_item; i++) {
			if (ix0[i]<x1 && x0<ix1[i] && 
				iy0[i]<y1 && y0<iy1[i]) {
				special=true;
				time=300;
			}
		}
	}
	
	// 特殊状態のとき
	else {
		
		// 特殊攻撃を行う：
		// 具体的な処理はSpecialAttack関数で行うとする。
		SpecialAttack();
		
		// 一定時間が過ぎたかどうかの判定：
		// 残り時間がなくなったら通常状態に戻る。
		if (time==0) special=false; else time--;
	}
}


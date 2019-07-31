void DeleteOpponent();
void DeleteShot();

void HitShot(
	float x0, float y0,    // ショットの当たり判定の左上座標
	float x1, float y1,    // ショットの当たり判定の右下座標
	float attack,          // ショットの攻撃力
	float ox0, float oy0,  // 対象の当たり判定の左上座標
	float ox1, float oy1,  // 対象の当たり判定の右下座標
	float endurance,       // 対象の耐久力
	bool invincible        // 対象が破壊不可能かどうか
) {
	// ショットが対象に当たった場合
	if (ox0<x1 && x0<ox1 && oy0<y1 && y0<oy1) {

		// 対象が無敵でない場合：
		// ショットの攻撃力で対象の耐久力を削り，
		// 耐久力が0になったら対象を消す。
		// 具体的な処理はDeleteOpponent関数で行うとする。
		if (!invincible) {
			endurance-=attack;
			if (endurance<0) DeleteOpponent();
		}
		
		// ショットを消す：
		// 具体的な処理はDeleteShot関数で行うとする。
		// ここでショットを消さないと，貫通弾になる。
		DeleteShot();
	}
}


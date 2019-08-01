void DeleteBullet(int id);
void DamageEnemy(int id);
void DeleteBarrier();

void Barrier1(
	float x0, float y0,        // バリアの当たり判定
	float x1, float y1,        // （左上座標，右下座標）
	float bx0[], float by0[],  // 弾の当たり判定
	float bx1[], float by1[],  // （左上座標，右下座標）
	int num_bullet,            // 弾の数
	float ex0[], float ey0[],  // 敵の当たり判定
	float ex1[], float ey1[],  // （左上座標，右下座標）
	int num_enemy,             // 敵の数
	int& damage,               // バリアに蓄積されたダメージ
	int max_damage             // バリアのダメージの限界値
) {
	// バリアと弾との当たり判定処理：
	// 弾が当たったら，弾を消し，バリアのダメージを増やす。
	// 弾を消す具体的な処理はDeleteBullet関数で行うとする。
	for (int i=0; i<num_bullet && damage<max_damage; i++) {
		if (bx0[i]<x1 && x0<bx1[i] && 
			by0[i]<y1 && y0<by1[i]) {
			DeleteBullet(i);
			damage++;
		}
	}

	// バリアと敵との当たり判定処理：
	// 敵が当たったら，敵にダメージを与え，
	// バリアのダメージも増やす。
	// 敵にダメージを与える具体的な処理は，
	// DamageEnemy関数で行うとする。
	for (int i=0; i<num_enemy && damage<max_damage; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			damage++;
		}
	}
	
	// ダメージが限界値を超えたとき：
	// バリアを消滅させる。
	// 消滅の具体的な処理はDeleteBarrier関数で行うとする。
	if (damage>=max_damage) DeleteBarrier();
}

void Barrier2(
	float x0, float y0,        // バリアの当たり判定
	float x1, float y1,        // （左上座標，右下座標）
	float bx0[], float by0[],  // 弾の当たり判定
	float bx1[], float by1[],  // （左上座標，右下座標）
	int num_bullet,            // 弾の数
	float ex0[], float ey0[],  // 敵の当たり判定
	float ex1[], float ey1[],  // （左上座標，右下座標）
	int num_enemy,             // 敵の数
	int& energy,               // バリアのエネルギー
	bool barrier_button        // バリアボタンの状態
) {
	// バリアを張る：
	// バリアボタンが押されており，
	// かつエネルギーがあるときには，バリアを張る。
	if (barrier_button && energy>0) {
	
		// バリアと弾との当たり判定処理：
		// 弾が当たったら，弾を消し，バリアのエネルギーを減らす。
		// 弾を消す具体的な処理はDeleteBullet関数で行うとする。
		for (int i=0; i<num_bullet && energy>0; i++) {
			if (bx0[i]<x1 && x0<bx1[i] && 
				by0[i]<y1 && y0<by1[i]) {
				DeleteBullet(i);
				energy--;
			}
		}

		// バリアと敵との当たり判定処理：
		// 敵が当たったら，敵にダメージを与え，
		// バリアのエネルギーを減らす。
		// 敵にダメージを与える具体的な処理は，
		// DamageEnemy関数で行うとする。
		for (int i=0; i<num_enemy && energy>0; i++) {
			if (ex0[i]<x1 && x0<ex1[i] && 
				ey0[i]<y1 && y0<ey1[i]) {
				DamageEnemy(i);
				energy--;
			}
		}

		// エネルギーの消費
		energy--;
	}
}



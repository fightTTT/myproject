void DamageEnemy(int id);
void DeleteBullet(int id);
void DeleteCapturedEnemy();
void Shot();

void CapturedEnemy(
	float& x0, float& y0,      // 味方になった敵の左上座標
	float& x1, float& y1,      // 味方になった敵の右下座標
	float ex0[], float ey0[],  // 他の敵の左上座標
	float ex1[], float ey1[],  // 他の敵の右下座標
	int num_enemy,             // 他の敵の数
	float bx0[], float by0[],  // 弾の左上座標
	float bx1[], float by1[],  // 弾の右下座標
	int num_bullet,            // 弾の数
	bool button                // ショットボタンの状態
) {
	static int damage;         // 現在のダメージ
	static int max_damage=40;  // ダメージの限界値

	// 敵との当たり判定処理：
	// 敵と衝突したら，敵にダメージを与え，
	// 自分もダメージを受ける。
	// ダメージ付与の具体的な処理は，
	// DamageEnemy関数で行うとする。
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			damage++;
		}
	}
	
	// 弾との当たり判定処理：
	// 弾と衝突したら，弾を消し，
	// 自分もダメージを受ける。
	// 消去の具体的な処理は，
	// DeleteBullet関数で行うとする。
	for (int i=0; i<num_bullet; i++) {
		if (bx0[i]<x1 && x0<bx1[i] && 
			by0[i]<y1 && y0<by1[i]) {
			DeleteBullet(i);
			damage++;
		}
	}
	
	// 援護射撃：
	// 自機のショット操作に合わせてショットを撃つ。
	// 発射の具体的な処理はShot関数で行うとする。
	if (button) Shot();

	// ダメージ判定：
	// ダメージが限界値まで蓄積したら消滅する。
	// 消滅の具体的な処理は，
	// DeleteCapturedEnemy関数で行うとする。
	if (damage>=max_damage) DeleteCapturedEnemy();
}

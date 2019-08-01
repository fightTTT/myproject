void DeleteBullet(int id);
void DamageEnemy(int id);

void Bomb(
	int& bomb_time,             // ボムの有効時間
	float x0, float y0,        // ボムの有効範囲の左上座標
	float x1, float y1,        // ボムの有効範囲の右下座標
	float bx0[], float by0[],  // 弾の左上座標
	float bx1[], float by1[],  // 弾の右下座標
	int num_bullet,            // 弾の数
	float ex0[], float ey0[],  // 敵の左上座標
	float ex1[], float ey1[],  // 敵の右下座標
	int num_enemy              // 敵の数
) {
	// ボムが有効な場合の処理
	if (bomb_time>0) {
	
		// 弾を消す：
		// 消去の具体的な処理は，
		// DeleteBullet関数で行うとする。
		for (int i=0; i<num_bullet; i++) {
			if (bx0[i]<x1 && x0<bx1[i] && 
				by0[i]<y1 && y0<by1[i]) {
				DeleteBullet(i);
			}
		}

		// 敵にダメージを与える：
		// ダメージ付与の具体的な処理は，
		// DamageEnemy関数で行うとする。
		for (int i=0; i<num_enemy; i++) {
			if (ex0[i]<x1 && x0<ex1[i] && 
				ey0[i]<y1 && y0<ey1[i]) {
				DamageEnemy(i);
			}
		}
	
		// ボムの有効時間を減らす
		bomb_time--;
	}
}


void DamageEnemy(int id);
void DeleteBullet(int id);
void Miss();

void Invincible(
	bool invincible,           // 無敵状態ならばtrue
	float x0, float y0,        // 自機の左上座標
	float x1, float y1,        // 自機の右下座標
	float ex0[], float ey0[],  // 敵の左上座標
	float ex1[], float ey1[],  // 敵の左上座標
	int num_enemy,             // 敵の数
	float bx0[], float by0[],  // 弾の左上座標
	float bx1[], float by1[],  // 弾の左上座標
	int num_bullet             // 弾の数
) {
	// 敵との当たり判定処理：
	// 敵とぶつかった場合，無敵状態ならば敵にダメージを与え，
	// 通常状態ならばミスとする。
	// ダメージ付与とミスの具体的な処理は，
	// DamageEnemy，Missの各関数で行うとする。
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			if (invincible) DamageEnemy(i); else Miss();
		}
	}
	
	// 弾との当たり判定処理：
	// 弾とぶつかった場合，無敵状態ならば弾を消し，
	// 通常状態ならばミスとする。
	// 消去とミスの具体的な処理は，
	// DeleteBullet，Missの各関数で行うとする。
	for (int i=0; i<num_bullet; i++) {
		if (bx0[i]<x1 && x0<bx1[i] && 
			by0[i]<y1 && y0<by1[i]) {
			if (invincible) DeleteBullet(i); else Miss();
		}
	}
}

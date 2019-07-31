void DeleteEnemy(int id);
void DeleteWeapon(int id);

void BreakableEnemy(
	int num_enemy,             // 敵の数
	float ex0[], float ey0[],  // 敵の当たり判定の左上座標
	float ex1[], float ey1[],  // 敵の当たり判定の右下座標
	float vit[],               // 敵の耐久力
	int num_weapon,            // 武器の数
	float wx0[], float wy0[],  // 武器の当たり判定の左上座標
	float wx1[], float wy1[],  // 武器の当たり判定の右下座標
	float str[]                // 武器の攻撃力
) {
	// 敵と武器の当たり判定処理：
	// 全ての敵と武器の組み合わせについて，
	// 武器が敵に当たったかどうかを判定する
	for (int i=0; i<num_enemy; i++) {
		for (int j=0; j<num_weapon; j++) {
			if (ex0[i]<wx1[j] && wx0[j]<ex1[i] && 
				ey0[i]<wy1[j] && wy0[j]<ey1[i]
			) {
				// 当たった場合：
				// 武器の攻撃力で敵の耐久力を削り，
				// 耐久力が0または負になったら敵を破壊する。
				// 破壊の具体的な処理は，
				// DeleteEnemy関数で行うとする。
				vit[i]-=str[j];
				if (vit[i]<=0) DeleteEnemy(i);
				
				// 敵に当たった武器は消す：
				// 具体的な処理はDeleteWeapon関数で行うとする。
				DeleteWeapon(j);
			}
		}
	}
}


void DeleteEnemy(int id);
void DeleteWeapon(int id);

// 敵のタイプを表す定数：
// 破壊できる，破壊できない，武器が当たらない
typedef enum {
	BREAKABLE, UNBREAKABLE, TRANSPARENT
} ENEMY_TYPE;

// 破壊できないものも含めた敵の処理
void BreakableEnemy2(
	int num_enemy,             // 敵の数
	ENEMY_TYPE type[],         // 敵のタイプ
	float ex0[], float ey0[],  // 敵の当たり判定の左上座標
	float ex1[], float ey1[],  // 敵の当たり判定の右下座標
	float vit[],               // 敵の耐久力
	int num_weapon,            // 武器の数
	float wx0[], float wy0[],  // 武器の当たり判定の左上座標
	float wx1[], float wy1[],  // 武器の当たり判定の右下座標
	float str[]                // 武器の攻撃力
) {
	// 全ての敵に関するループ
	for (int i=0; i<num_enemy; i++) {
		
		// 武器に当たらない敵の場合：
		// 当たり判定処理は行わず，
		// 次の敵の処理に移る。
		if (type[i]==TRANSPARENT) continue;
		
		// 敵と武器との当たり判定処理
		for (int j=0; j<num_weapon; j++) {
			if (ex0[i]<wx1[j] && wx0[j]<ex1[i] && 
				ey0[i]<wy1[j] && wy0[j]<ey1[i]
			) {
				// 破壊できる敵に当たった場合：
				// 武器の攻撃力で敵の耐久力を削り，
				// 耐久力が0または負になったら敵を破壊する。
				// 破壊の具体的な処理は，
				// DeleteEnemy関数で行うとする。
				if (type[i]==BREAKABLE) {
					vit[i]-=str[j];
					if (vit[i]<=0) DeleteEnemy(i);
				}
				
				// 敵に当たった武器は消す：
				// 具体的な処理はDeleteWeapon関数で行うとする。
				DeleteWeapon(j);
			}
		}
	}
}



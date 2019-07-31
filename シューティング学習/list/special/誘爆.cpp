void DestroyEnemy(int id);
void CreateExplosion(float x, float y);

void InducedExplosion(
	float ex0[], float ey0[],  // 敵の左上座標
	float ex1[], float ey1[],  // 敵の右下座標
	int num_enemy,             // 敵の数
	float x0[], float y0[],    // 爆風の左上座標
	float x1[], float y1[],    // 爆風の右下座標
	int num_explosion          // 爆風の数
) {
	// 敵と爆風の当たり判定処理：
	// 全ての敵と爆風との間で当たり判定処理を行い，
	// 敵が爆風に当たったら破壊する。
	// そして敵と同じ座標に新たな爆風を生成する。
	// 破壊と生成の具体的な処理は，
	// DestroyEnemy，CreateExplosionの各関数で行うとする。
	for (int i=0; i<num_enemy; i++) {
		for (int j=0; j<num_explosion; j++) {
			if (ex0[i]<x1[j] && x0[j]<ex1[i] && 
				ey0[i]<y1[j] && y0[j]<ey1[i]) {
				DestroyEnemy(i);
				CreateExplosion(ex0[i], ey0[i]);
			}
		}
	}
}

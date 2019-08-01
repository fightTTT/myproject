void DamageEnemy(int id);

void MoveReflectShot(
	float& x0, float& y0,      // ショットの左上座標
	float& x1, float& y1,      // ショットの右下座標
	float& vx, float& vy,      // ショットの速度（水平，垂直）
	float gx0[], float gy0[],  // 地形の左上座標
	float gx1[], float gy1[],  // 地形の右下座標
	int num_ground,            // 地形の数
	float ex0[], float ey0[],  // 敵の左上座標
	float ex1[], float ey1[],  // 敵の右下座標
	int num_enemy              // 敵の数
) {
	// 地形との当たり判定処理：
	// ショットを垂直方向に進めた座標について，
	// 地形に当たるかどうかを判定する。
	// 地形に当たった場合には，垂直方向の速度を逆にして，
	// ループから抜ける。
	for (int i=0; i<num_ground; i++) {
		if (gx0[i]<x1 && x0<gx1[i] && 
			gy0[i]<y1+vy && y0+vy<gy1[i]) {
			vy=-vy;
			break;
		}
	}
	
	// ショットを進める
	x0+=vx; y0+=vy;
	x1+=vx; y1+=vy;

	// 敵との当たり判定処理：
	// 敵に当たった場合には，敵にダメージを与えて，
	// ループから抜ける。
	// ダメージの具体的な処理はDamageEnemy関数で行うとする。
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			break;
		}
	}
}


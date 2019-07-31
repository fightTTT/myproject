void DeleteEnemy(int id);

void DeleteEnemy(int id);

void OrbitalFlight(
	int num_enemy,           // 敵の数
	float ex[], float ey[],  // 敵の座標
	int index[],             // 軌道データを指すインデックス
	int num_orbit,           // 軌道データの要素数
	float ox[], float oy[]   // 軌道データ（座標）
) {
	for (int i=0; i<num_enemy; i++) {
		
		// 敵座標の更新：
		// 軌道データを読み出して，敵の新しい座標とする。
		ex[i]=ox[index[i]];
		ey[i]=oy[index[i]];
		
		// インデックス（データの読み出し位置）を進める：
		// 軌道データの最後に達したら敵を消す。
		// 敵を消す具体的な処理はDeleteEnemy関数で行うとする。
		// 
		index[i]++;
		if (index[i]==num_orbit) DeleteEnemy(i);
	}
}



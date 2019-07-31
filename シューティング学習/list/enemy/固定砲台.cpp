void MoveFixedBattery(
	int num_enemy,           // 敵（固定砲台）の数
	float ex[], float ey[],  // 敵（固定砲台）の座標
	float svx, float svy     // 背景の移動速度（スクロール速度）
) {
	// 全ての固定砲台を背景と同じ速度で動かす
	for (int i=0; i<num_enemy; i++) {
		ex[i]+=svx;
		ey[i]+=svy;
	}
}


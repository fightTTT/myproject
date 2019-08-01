void ShotPower(
	float& x, float& y,  // ショットの座標
	float vx, float vy,  // ショットの速度
	float& power,        // ショットの威力
	float attenuation    // 威力が減衰する度合い
) {
	// ショットを移動させる
	x+=vx; y+=vy;
	
	// 移動するたびにショットの威力を弱める
	power-=attenuation;
}


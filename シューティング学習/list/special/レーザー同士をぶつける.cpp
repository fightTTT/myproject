void DeleteMyLaser(int id);
void DeleteEnemyLaser(int id);
void SpecialAttack();

void LaserCollision(
	float mx0[], float my0[],  // 自機レーザーの一部の左上座標
	float mx1[], float my1[],  // 自機レーザーの一部の右下座標
	int num_my_lasers,         // 自機レーザーの部分の数
	float ex0[], float ey0[],  // 敵レーザーの一部の左上座標
	float ex1[], float ey1[],  // 敵レーザーの一部の右下座標
	int num_enemy_lasers       // 敵レーザーの部分の数
) {
	static int energy=0;        // エネルギー
	static int min_energy=100;  // 攻撃の発生に必要なエネルギー
	
	// レーザー同士の当たり判定処理：
	// 自機レーザーと敵レーザーの各部分同士がぶつかったら，
	// 2つの部分を消滅させてエネルギーを増やす。
	// 消滅の具体的な処理は，DeleteMyLaser，
	// DeleteEnemyLaserの各関数で行うとする。
	for (int i=0; i<num_my_lasers; i++) {
		for (int j=0; j<num_enemy_lasers; j++) {
			if (ex0[j]<mx1[i] && mx0[i]<ex1[j] && 
				ey0[j]<my1[i] && my0[i]<ey1[j]) {
				DeleteMyLaser(i);
				DeleteEnemyLaser(j);
				energy++;
			}
		}
	}
	
	// 攻撃の発生：
	// エネルギーが必要量に達していたら，
	// 強力な攻撃を発生させる。
	// 発生の具体的な処理はSpecialAttack関数で行うとする。
	if (energy>=min_energy) SpecialAttack();
}


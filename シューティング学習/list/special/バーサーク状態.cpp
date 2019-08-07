void NormalAttack();
void SpecialAttack();
bool HitShot(int id);
bool HitEnemy(int id);
bool HitBullet(int id);
void DeleteShot(int id);
void Miss();
void DamageEnemy(int id);
void DeleteBullet(int id);

// 自機の状態（通常，バーサーク，弱い）
typedef enum {
	NORMAL, BERSERK, WEAK
} STATE_TYPE;

// バーサーク状態の処理
void Berserk(
	int num_shot,   // 味方のショットの数
	int num_enemy,  // 敵の数
	int num_bullet  // 弾（敵弾）の数
) {
	static STATE_TYPE state=NORMAL;  // 自機の状態（最初は通常）
	static int energy=0;             // エネルギー
	static int berserk_energy=100;   // バーサーク状態の発動に
	                                 // 必要なエネルギー
	static int time;                 // 効果の残り時間
	
	// 状態に応じて分岐する
	switch (state) {
		
		// 通常状態
		case NORMAL:

			// 通常攻撃：
			// 具体的な処理はNormalAttack関数で行うとする。
			NormalAttack();

			// 敵や弾との当たり判定処理：
			// 当たるとミスになる。
			// 判定や結果の具体的な処理はHitEnemy，
			// HitBullet，Missの各関数で行うとする。
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) Miss();
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) Miss();

			// 味方のショットとの当たり判定処理：
			// エネルギーを溜める。
			// 判定や結果の具体的な処理はHitShot，
			// DeleteShotの各関数で行うとする。
			for (int i=0; i<num_shot; i++) {
				if (HitShot(i)) {
					energy++;
					DeleteShot(i);
				}
			}

			// エネルギー量の判定：
			// エネルギーが十分に溜まったら
			// バーサーク状態に移行する。
			// エネルギーは自然に減っていく。
			if (energy>=berserk_energy) {
				state=BERSERK;
				time=300;
			} else {
				energy--;
			}

			break;
		
		// バーサーク状態
		case BERSERK:

			// 特殊攻撃：
			// 具体的な処理はSpecialAttack関数で行うとする。
			SpecialAttack();

			// 敵や弾との当たり判定処理：
			// 敵にダメージを与え，弾は消す。
			// 結果の具体的な処理はDamageEnemy，
			// DeleteBulletの各関数で行うとする。
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) DamageEnemy(i);
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) DeleteBullet(i);
			
			// 残り時間が切れたら弱い状態に移行する
			time--;
			if (time<=0) {
				state=WEAK;
				time=200;
			}
			
			break;
			
		// 弱い状態
		case WEAK:
			
			// 敵や弾との当たり判定処理：
			// 当たるとミスになる。
			for (int i=0; i<num_enemy; i++)
				if (HitEnemy(i)) Miss();
			for (int i=0; i<num_bullet; i++)
				if (HitBullet(i)) Miss();

			// 残り時間が切れたら通常状態に移行する
			time--;
			if (time<=0) {
				state=NORMAL;
				energy=0;
			}
			
			break;
	}
}


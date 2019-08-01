// 敵を表す構造体
typedef struct {
	bool Locked;  // ロックされているかどうか
	float X, Y;   // 座標
} ENEMY_TYPE;
#define MAX_ENEMIES 100
static ENEMY_TYPE Enemy[MAX_ENEMIES];

bool Hit(float x, float y, ENEMY_TYPE& enemy);
void ShootLockOnLaser(ENEMY_TYPE& enemy);

// ロックオンの使用可能数
static int AvailLocks=8;

// ロックオンレーザーの発射
void LockOnLaser(
	float sx, float sy,  // 照準の座標
	bool button          // ボタンの状態（押されたときtrue）
) {
	// ロックオンの使用可能数が1以上のとき：
	// 全ての敵と照準との当たり判定処理を行い，
	// 照準と重なった敵にはロックマークを付ける。
	// 当たり判定の具体的な処理はHit関数で行うとする。
	for (int i=0; AvailLocks>0 && i<MAX_ENEMIES; i++) {
		if (!Enemy[i].Locked && Hit(sx, sy, Enemy[i])) {
			Enemy[i].Locked=true;

			// ロックオンの使用可能数を減らす：
			// 敵にレーザーが命中したら，使用可能数を増やす。
			AvailLocks--;
		}
	}

	// ボタンが押された場合：
	// ロックマークが付いた全ての敵に向けてレーザーを発射する。
	// 発射の具体的な処理はShootLockOnLaser関数で行うとする。
	if (button) {
		for (int i=0; i<MAX_ENEMIES; i++) {
			if (Enemy[i].Locked) ShootLockOnLaser(Enemy[i]);
		}
	}
}


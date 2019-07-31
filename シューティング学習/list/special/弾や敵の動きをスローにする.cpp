void MoveEnemy();
void MoveBullet();

void Slowing(
	int& gauge,  // スロー状態にするために必要なゲージ
	bool button  // スローボタンを押しているかどうか
) {
	// タイマー：
	// スロー状態のときに行動回数を調整するために使う。
	static int time=1;

	// 敵と弾を動かす：
	// 通常状態のときには毎回動かし，
	// スロー状態のときには2回に1回だけ動かす。
	// 移動の具体的な処理は，
	// MoveEnemy，MoveBulletの各関数で行うとする。
	if (!button || (gauge>0 && time==0)) {
		MoveEnemy();
		MoveBullet();
	}
	
	// ペナルティ：
	// ゲージが0なのにスローボタンを押していたら，
	// ペナルティとして弾をもう1度動かす。
	// 結果として，弾は通常の2倍の速度で動く。
	if (button && gauge==0) {
		MoveBullet();
	}

	// タイマーの更新
	if (time>0) time--; else time=1;
}


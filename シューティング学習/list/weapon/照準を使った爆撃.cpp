void Explode();
void DrawMyShip(float x, float y);
void DrawScope(float x, float y);
void DrawTarget(float x, float y);
void DrawBomb(float x, float y);

void SightedBomb(
	float x, float y,        // 自機の座標
	float sx, float sy,      // 照準の座標
	float bvx, float bvy,    // 爆弾の速度
	bool button              // ボタンの状態（押されたときtrue）
) {
	// 爆弾の状態
	static bool bombing=false;  // 爆撃中かどうか
	static float bx, by;        // 爆弾の座標
	static float tx, ty;        // 着弾点の座標

	// 爆撃中ではないとき：
	// ボタンが押されたら爆撃する。
	// 爆弾の初期座標と着弾点の座標を設定する。
	if (!bombing) {
		if (button) {
			bombing=true;
			bx=x; by=y;
			tx=sx; ty=sy;
		}
	}
	
	// 爆撃中のとき：
	// 爆弾を移動させる。
	// 爆弾が着弾点に到達したら爆発させる。
	// 爆発の具体的な処理はExplode関数で行うとする。
	else {
		bx+=bvx; by+=bvy;
		if (bx==tx && by==ty) {
			Explode();
			bombing=false;
		}
	}
	
	// 自機と照準を描く：
	// 具体的な処理はDrawMyShip関数とDrawScope関数で行うとする。
	// 照準と地上物との当たり判定処理を行えば，
	// 照準の端を点滅させることもできる。
	DrawMyShip(x, y);
	DrawScope(sx, sy);

	// 爆撃中の場合には着弾点と爆弾を描く：
	// 具体的な処理はDrawTarget関数とDrawBomb関数で行うとする。
	if (bombing) {
		DrawTarget(tx, ty);
		DrawBomb(bx, by);
	}
}


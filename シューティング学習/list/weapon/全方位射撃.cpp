#include <math.h>

void DirectedShot(float x, float y, float dir);

void TurnMarker(
	float& x, float& y,     // 自機の座標
	float speed,            // 自機の速さ
	bool left, bool right,  // スティックの状態（左右方向）
	bool up, bool down,     // スティックの状態（上下方向）
	bool turn_button,       // 旋回ボタンの状態
	bool shot_button        // ショットボタンの状態
) {
	static bool turning;        // 旋回中ならばtrue
	static float mx, my;        // ターンマーカーの座標
	static float rad=M_PI*3/2;  // 旋回角度（M_PIは円周率）
	static float d=10;          // 自機とターンマーカーの距離
	
	// 旋回の開始：
	// ターンマーカーの座標を算出する。
	if (!turning && turn_button) {
		turning=true;
		mx=x-d*cos(rad);
		my=y-d*sin(rad);
	}
	
	// 旋回の終了
	if (!turn_button) turning=false;
	
	// 自機の移動
	if (up   ) y-=speed;
	if (down ) y+=speed;
	if (left ) x-=speed;
	if (right) x+=speed;
	
	// 旋回中ならば旋回角度を計算する
	if (turning) rad=-atan2(x-mx, y-my);
	
	// ショットの発射：
	// 自機が向いている方向にショットを撃つ。
	// 発射方向はradとは反対方向（180°=πラジアンずれる）。
	// 発射の具体的な処理はDirectedShot関数で行うとする。
	if (shot_button) DirectedShot(x, y, rad+M_PI);
}


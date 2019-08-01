#include <math.h>

void Shot(float x, float y, float vx, float vy);

void MoveSight2(
	float& x, float& y,       // 自機の座標
	float speed,              // 自機の速さ
	bool up1, bool down1,     // 自機用スティック入力1（上下）
	bool left1, bool right1,  // 自機用スティック入力1（左右）
	float& sx, float& sy,     // 照準の座標
	float sight_speed,        // 照準の速さ
	bool up2, bool down2,     // 照準用スティック入力2（上下）
	bool left2, bool right2,  // 照準用スティック入力2（左右）
	bool button,              // ショットボタンの入力
	float shot_speed          // ショットの速さ
) {
	// 自機を動かす
	if (up1   ) y-=speed;
	if (down1 ) y+=speed;
	if (left1 ) x-=speed;
	if (right1) x+=speed;

	// 照準を動かす
	if (up2   ) sy-=sight_speed;
	if (down2 ) sy+=sight_speed;
	if (left2 ) sx-=sight_speed;
	if (right2) sx+=sight_speed;

	// ショットを撃つ：
	// ショットボタンが押されたら，
	// 自機から照準に向かってショットを撃つ。
	// 発射の具体的な処理はShot関数で行うとする。
	if (button) {
		float vx=sx-x, vy=sy-y;
		if (vx!=0 || vy!=0) {
			float d=sqrt(vx*vx+vy*vy);
			vx*=shot_speed/d;
			vy*=shot_speed/d;
			Shot(x, y, vx, vy);
		}
	}
}


#include <math.h>

void InitAimingBullet(
	float mx, float my,   // 自機の座標
	float ex, float ey,   // 敵の座標
	float speed,          // 弾の速さ
	float& x, float& y,   // 弾の座標
	float& vx, float& vy  // 弾の速度
) {
	// 弾の座標を設定する
	x=ex; y=ey;

	// 目標までの距離dを求める
	float d=sqrt((mx-ex)*(mx-ex)+(my-ey)*(my-ey));

	// 速さが一定値speedになるように速度(vx,vy)を求める：
	// 目標までの距離dが0のときには下方向に発射する。
	if (d) {
		vx=(mx-ex)/d*speed;
		vy=(my-ey)/d*speed;
	} else {
		vx=0;
		vy=speed;
	}
}

void MoveAimingBullet(
	float& x, float& y,  // 弾の座標
	float vx, float vy   // 弾の速度
) {
	// 弾の座標(x,y)に速度(vx,vy)を加える
	x+=vx;
	y+=vy;
}


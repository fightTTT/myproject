#include <math.h>

void MoveSimpleHomingBullet(
	float& x, float& y,  // 弾の座標
	float mx, float my,  // 自機の座標
	float speed          // 弾の速さ
) {
	// 目標までの距離dを求める
	float d=sqrt((mx-x)*(mx-x)+(my-y)*(my-y));

	// 弾の速度(vx, vy)を求める：
	// 速さが一定値speedになるようにする。
	// 目標までの距離dが0のときには速度を下方向にする。
	float vx, vy;
	if (d) {
		vx=(mx-x)/d*speed;
		vy=(my-y)/d*speed;
	} else {
		vx=0;
		vy=speed;
	}

	// 弾の座標(x,y)を更新して，弾を移動させる
	x+=vx;
	y+=vy;
}


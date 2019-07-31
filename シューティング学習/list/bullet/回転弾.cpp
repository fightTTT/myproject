#include <math.h>

void MoveLoopingBullet(
	float& x, float& y,    // 弾の座標
	float& vx, float& vy,  // 弾の速度
	float cx, float cy,    // 回転中心の座標
	float r,               // 半径
	float theta,           // 角度（ラジアン）
	float omega            // 1回の移動で変化する角度（ラジアン）
) {
	// 角度を変化させる
	theta+=omega;

	// 位置を計算する
	x=cx+r*cos(theta);
	y=cy+r*sin(theta);

	// 弾の速度（必要な場合だけ）
	vx=-r*omega*sin(theta);
	vy= r*omega*cos(theta);
}

void MoveLoopingBullet2(
	float& x, float& y,    // 弾の座標
	float& vx, float& vy,  // 弾の速度
	float cx, float cy,    // 回転中心の座標
	float& r,              // 半径
	float vr,              // 半径の変化
	float theta,           // 角度（ラジアン）
	float omega            // 1回の移動で変化する角度（ラジアン）
) {
	// 角度を変化させる
	theta+=omega;
	
	// 半径を変化させる
	r+=vr;

	// 位置を計算する
	x=cx+r*cos(theta);
	y=cy+r*sin(theta);

	// 弾の速度（必要な場合だけ）
	vx=-r*omega*sin(theta);
	vy= r*omega*cos(theta);
}


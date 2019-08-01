#include <math.h>

void InitCircleBullets(
	int n,                   // 弾の数
	float speed,             // 弾の速さ
	bool odd,                // 奇数パターンのときtrue
	float vx[], float vy[]   // 円形弾の速度
) {
	// 弾と弾との間の角度を計算する
	float rad_step=M_PI*2/n;

	// 最初の弾の角度を計算する：
	// 奇数パターンのときにはrad_step/2だけずらす。
	float rad=odd ? rad_step/2 : 0;

	// n個の弾の速度を決める：
	// 速さspeedで角度radの方向に飛ぶ弾の速度を求める。
	// これは方向弾を飛ばす処理の応用。
	for (int i=0; i<16; i++, rad+=rad_step) {
		vx[i]=cos(rad)*speed;
		vy[i]=sin(rad)*speed;
	}
}


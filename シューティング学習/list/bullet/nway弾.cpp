#include <math.h>

void RotateVelocity(
	float theta,           // 回転角度
	float vx0, float vy0,  // 元の速度
	float& vx, float& vy   // 回転後の速度
) {
	// thetaをラジアンに変換し，cosとsinを求める：
	// M_PIは円周率。
	float rad=M_PI/180*theta;
	float c=cos(rad), s=sin(rad);

	// 速度ベクトル(vx0,vy0)を回転させた(vx,vy)を求める
	vx=vx0*c-vy0*s;
	vy=vx0*s+vy0*c;
}

void InitNWayBullets(
	float vx0, float vy0,    // 中心となる弾の速度
	float theta,             // 弾と弾の間の角度
	int n,                   // 弾の数
	float vx[], float vy[]   // n-way弾の速度
) {
	// 弾と弾の間の角度をラジアンに変換する
	float rad_step=M_PI/180*theta;
	
	// 端の弾と中心の弾との間の角度を計算する
	float rad=n%2 ? -n/2*rad_step : (-n/2+0.5)*rad_step;

	// n個の弾の速度を計算する
	for (int i=0; i<n; i++, rad+=rad_step) {
		
		// (vx[i],vy[i])を求める：
		// 速度ベクトル(vx0,vy0)をradだけ回転させる。
		float c=cos(rad), s=sin(rad);
		vx[i]=vx0*c-vy0*s;
		vy[i]=vx0*s+vy0*c;
	}
}


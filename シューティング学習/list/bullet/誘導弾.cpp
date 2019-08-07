#include <math.h>

void MoveHomingBullet(
	float& x, float& y,    // 弾の座標
	float& vx, float& vy,  // 弾の速度
	float mx, float my,    // 自機の座標
	float speed,           // 弾の速さ
	float theta            // 旋回角度の上限
) {
	// 弾の元の速度
	float vx0=vx, vy0=vy;

	// 自機方向の速度ベクトル(vx1,vy1)を求める
	float vx1, vy1;
	float d=sqrt((mx-x)*(mx-x)+(my-y)*(my-y));
	if (d) {
		vx1=(mx-x)/d*speed;
		vy1=(my-y)/d*speed;
	} else {
		vx1=0;
		vy1=speed;
	}

	// 右回り旋回角度上限の速度ベクトル(vx2,vy2)を求める：
	// M_PIは円周率。
	float rad=M_PI/180*theta;
	float vx2=cos(rad)*vx0-sin(rad)*vy0;
	float vy2=sin(rad)*vx0+cos(rad)*vy0;

	// 自機方向と旋回角度上限のどちらに曲がるかを決める
	if (vx0*vx1+vy0*vy1<=vx0*vx2+vx0*vy2) {
		
		// 自機方向が旋回可能範囲内の場合：
		// 自機方向に曲がる
		vx=vx0;
		vy=vy0;

	} else {

		// 自機方向が旋回可能範囲外の場合：
		// 左回り旋回角度上限の速度ベクトル(vx3,vy3)を求める
		float vx3= cos(rad)*vx0+sin(rad)*vy0;
		float vy3=-sin(rad)*vx0+cos(rad)*vy0;
		
		// 弾から自機への相対位置ベクトル(px,py)を求める
		float px=mx-x, py=my-y;
		
		// 右回りか左回りかを決める
		if (px*vx2+py*vy2<=px*vx3+py*vy3) {

			// 右回りの場合
			vx=vx2;
			vy=vy2;

		} else {

			// 左回りの場合
			vx=vx3;
			vy=vy3;

		}
	}

	// 弾の座標(x,y)を更新して，弾を移動させる
	x+=vx;
	y+=vy;
}


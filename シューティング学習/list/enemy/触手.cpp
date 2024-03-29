#include <math.h>

void MoveTentacle(
	float x[], float y[],  // 各パーツの座標
	int num_part,          // パーツの数
	float tx, float ty,    // 目標の座標
	float v,               // 先端が移動する速さ
	float limit,           // 先端と根元の最大距離
	int num_loop           // 計算の繰り返し回数
) {
	// 先端の座標と根元の座標
	float hx=x[0], hy=y[0];
	float rx=x[num_part-1], ry=y[num_part-1];

	// 目標の方向に先端を動かす
	hx+=(tx>=hx+v ? v : (tx<=hx-v ? -v : 0));
	hy+=(ty>=hy+v ? v : (ty<=hy-v ? -v : 0));

	// 先端の移動範囲を制限する：
	// 先端と根元との距離が限界値を超えていたら，
	// 移動可能範囲内に戻す。
	float dx=hx-rx, dy=hy-ry;
	float d=sqrt(dx*dx+dy*dy);
	if (d>limit) {
		hx=dx*limit/d+rx;
		hy=dy*limit/d+ry;
	}

	// 中間部分の座標を計算する：
	// 隣接部分の座標の平均をとる。
	// 計算は先端から根元に向かって行う。
	// 必要に応じて計算を複数回繰り返す。
	x[0]=hx; y[0]=hy;
	for (int l=0; l<num_loop; l++) {
		for (int i=1; i<num_part-1; i++) {
			x[i]=(x[i-1]+x[i+1])/2;
			y[i]=(y[i-1]+y[i+1])/2;
		}
	}
}


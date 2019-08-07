#include <math.h>

// 自機の位置を格納するテーブル
int mpos[360][2];

// テーブルを作る：
// M_PIは円周率。
void MakeTable() {
	for (int i=0; i<360; i++) {
		mpos[i][0]=cos(M_PI/180*i)*1000;
		mpos[i][1]=sin(M_PI/180*i)*1000;
	}
}

void InitDirectedBulletDDA2(
	int theta,         // 発射角度
	int ex, int ey,    // 敵の座標
	int& x, int& y,    // 弾の座標
	int& vx, int& vy,  // 弾の移動方向
	int& dx, int& dy,  // X方向とY方向の差分
	int& diff          // 誤差
) {
	// 仮想的な自機の位置をテーブルから読み出す
	int dir=(theta%360+360)%360;
	int mx=mpos[dir][0];
	int my=mpos[dir][1];

	// あとはDDAを使って自機の方向に弾を飛ばす処理と同じ

	// 弾の座標を設定する
	x=ex; y=ey;

	// 弾の移動方向(vx,vy)を求める：値は1または-1
	vx=mx>ex?1:-1;
	vy=my>ey?1:-1;

	// 目標に対するX方向とY方向の差分の絶対値(dx,dy)を求める
	dx=mx>=ex?mx-ex:ex-mx;
	dy=my>=ey?my-ey:ey-my;

	// 誤差diff：dx>=dyのときはdx/2，dx<dyのときはdy/2とする
	diff=dx>=dy?dx/2:dy/2;
}


#include <math.h>

void MoveJoints(
	int num_joint,         // 関節の数
	float x[], float y[],  // 関節の座標
	float rad[],           // 関節の回転角度
	float vrad,            // 関節が回転する速さ
	float lrad,            // 回転角度の限界値
	float dist,            // 関節間の距離
	float tx, float ty     // 目標の座標
) {
	int i;
	float c, s;
	
	// 前半の処理：
	// 先端から根元に向かって関節の角度を決める。
	c=(float)cos(vrad);
	s=(float)sin(vrad);
	for (i=1; i<num_joint; i++) {
		float dxt, dyt;       // 関節から目標へのベクトル
		float dxn, dyn;       // 関節から先端へのベクトル
		float dxr=0, dyr=0;   // 右回りのベクトル
		float dxl=0, dyl=0;   // 左回りのベクトル
		float dpn, dpr, dpl;  // 内積（回らない，右回り，左回り）
		
		// 関節から目標へのベクトルの計算
		dxt=tx-x[i];
		dyt=ty-y[i];

		// 関節から先端へのベクトルと内積の計算
		// （回らない場合のベクトル）
		dxn=x[0]-x[i];
		dyn=y[0]-y[i];
		dpn=dxt*dxn+dyt*dyn;
		
		// 右回りのベクトルの計算：
		// 回転角度の限界を超えたときには回さない
		if (rad[i]+vrad<=lrad) {
			dxr=c*dxn-s*dyn;
			dyr=s*dxn+c*dyn;
			dpr=dxt*dxr+dyt*dyr;
		} else dpr=dpn;
		
		// 左回りのベクトルの計算：
		// 回転角度の限界を超えたときには回さない
		if (rad[i]-vrad>=-lrad) {
			dxl= c*dxn+s*dyn;
			dyl=-s*dxn+c*dyn;
			dpl=dxt*dxl+dyt*dyl;
		} else dpl=dpn;
		
		// 回転方向の選択：
		// 内積を比較して，回転を3通りの中から選ぶ。
		// 先端を回転させて，新しい先端の位置を求める。
		if (dpr>dpn && dpr>dpl) {
			rad[i]+=vrad;
			x[0]=x[i]+dxr;
			y[0]=y[i]+dyr;
		}
		if (dpl>dpn && dpl>dpr) {
			rad[i]-=vrad;
			x[0]=x[i]+dxl;
			y[0]=y[i]+dyl;
		}
	}
	
	// 後半の処理：
	// 根元から先端に向かって関節の位置を求める。
	float px=dist, py=0, qx, qy;
	for (i=num_joint-2; i>=0; i--) {
		c=(float)cos(rad[i+1]);
		s=(float)sin(rad[i+1]);
		qx=c*px-s*py;
		qy=s*px+c*py;
		x[i]=x[i+1]+qx;
		y[i]=y[i+1]+qy;
		px=qx;
		py=qy;
	}
}

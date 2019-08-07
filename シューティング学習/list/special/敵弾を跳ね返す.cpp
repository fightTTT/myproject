#include <math.h>

void DeleteBullet(int id);
void Shot(float x, float y, float vx, float vy);

void ReflectBullet(
	float fx0, float fy0,    // フィールドの左上座標
	float fx1, float fy1,    // フィールドの右下座標
	int num_bullet,          // 弾の数
	float x0[], float y0[],  // 弾の左上座標
	float x1[], float y1[],  // 弾の右下座標
	float x[], float y[],    // 弾の中心座標
	float ex[], float ey[],  // 弾を撃った敵の中心座標
	float speed              // ショットの速さ
) {
	// 全ての弾に関して処理を行う
	for (int i=0; i<num_bullet; i++) {
	
		// 弾とフィールドとの当たり判定処理：
		// 弾がフィールドに接触したら，
		// 弾を消して，同じ位置から敵に向かってショットを撃つ。
		if (fx0<x1[i] && x0[i]<fx1 && 
			fy0<y1[i] && y0[i]<fy1) {

			// 弾の消去：
			// 具体的な処理はDeleteBullet関数で行うとする。
			DeleteBullet(i);
			
			// ショットの発射：
			// 敵に向かってショットを撃つ。
			// 発射の具体的な処理はShot関数で行うとする。
			float vx=ex[i]-x[i], vy=ey[i]-y[i];
			if (vx!=0 || vy!=0) {
				float d=sqrt(vx*vx+vy*vy);
				vx*=speed/d;
				vy*=speed/d;
				Shot(x[i], y[i], vx, vy);
			}
		}
	}
}


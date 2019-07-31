// レーザーの各部分を表す構造体
typedef struct LASER_STRUCT {
	float X, Y;                 // 左上座標
	float W, H;                 // 幅と高さ
	float VX, VY;               // 速度
	float OldX, OldY;           // 古い座標
	struct LASER_STRUCT* Prec;  // 1つ前の部分
	                            // （先頭部分の場合にはNULL）
} LASER_TYPE;

// レーザーを動かす関数
void MoveReflectLaser(
	LASER_TYPE* laser,         // レーザーの1つの部分
	float gx0[], float gy0[],  // 地形の左上座標
	float gx1[], float gy1[],  // 地形の右下座標
	int num_ground             // 地形の数
) {
	// 先端部分の場合：
	// 地形で反射するショットの処理と同じ。
	if (!laser->Prec) {

		// 地形との当たり判定処理：
		// 先端部分を垂直方向に進めた座標(X, Y+VY)について，
		// 地形に当たるかどうかを判定する。
		// 地形に当たった場合には，垂直方向の速度を逆にして，
		// ループから抜ける。
		for (int i=0; i<num_ground; i++) {
			if (gx0[i]<laser->X+laser->W &&
				laser->X<gx1[i] && 
				gy0[i]<laser->Y+laser->W+laser->VY &&
				laser->Y+laser->VY<gy1[i]
			) {
				laser->VX=-laser->VX;
				break;
			}
		}

		// 先端部分を進める
		laser->X+=laser->VX;
		laser->Y+=laser->VY;
	}
	
	// 先端部分以外の場合：
	// 1つ前の部分を追いかける。
	// 1つ前の部分の古い座標へ移動する。
	else {
		laser->X=laser->Prec->OldX;
		laser->Y=laser->Prec->OldY;
	}
}


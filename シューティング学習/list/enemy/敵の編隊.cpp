#include <stdlib.h>

// 敵の間隔
#define INTERVAL 6

// 敵の情報（構造体）
typedef struct ENEMY_STRUCT {
	float X, Y;                 // 現在の座標
	float OldX[INTERVAL];       // 古いX座標
	float OldY[INTERVAL];       // 古いY座標
	int Index;                  // 最も古い座標を指すインデックス
	struct ENEMY_STRUCT* Prec;  // 1つ前の敵
} ENEMY;

void MoveEnemy(int id);
ENEMY* NewEnemyType();

// 編隊飛行の処理
void Formation(
	int num_enemy,  // 敵の数
	ENEMY* enemy[]  // 敵の情報（構造体へのポインタ）
) {
	// 敵を動かす
	int i;
	for (i=0; i<num_enemy; i++) {
		ENEMY* self=enemy[i];
		ENEMY* prec=self->Prec;
		
		// 先頭以外の敵を動かす：
		// 1つ前の敵が保存している古い座標のうち，
		// もっとも古いものを自分の座標にする。
		if (prec) {
			self->X=prec->OldX[prec->Index];
			self->Y=prec->OldY[prec->Index];
		}
		
		// 先頭の敵を動かす：
		// 具体的な処理はMoveEnemy関数で行うとする。
		else {
			MoveEnemy(i);
		}
	}

	// 古い座標を記録する：
	// 最も古い座標を新しい座標で上書きし，
	// インデックスを更新する。
	for (i=0; i<num_enemy; i++) {
		ENEMY* self=enemy[i];
		self->OldX[self->Index]=self->X;
		self->OldY[self->Index]=self->Y;
		self->Index=(self->Index+1)%INTERVAL;
	}
}

// 編隊の生成
void CreateFormation(
	float x, float y,  // 生成地点の座標
	int count          // 編隊を構成する敵の数
) {
	ENEMY* enemy;      // 敵を表す構造体へのポインタ
	ENEMY* prec=NULL;  // 1つ前の敵を指すポインタ
	
	// 編隊を構成する敵を作る：
	// 敵の構造体を確保し，座標を初期化する。
	// 構造体確保の具体的な処理はNewEnemyType関数で行うとする。
	for (int i=0; i<count; i++, prec=enemy) {
		enemy=NewEnemyType();
		enemy->X=x;
		enemy->Y=y;
		for (int j=0; j<INTERVAL; j++) {
			enemy->OldX[j]=x;
			enemy->OldY[j]=y;
		}
		enemy->Index=0;

		// 先頭以外の敵は1つ前の敵を参照し，
		// 先端の敵はNULLを参照する。
		enemy->Prec=prec;
	}
}


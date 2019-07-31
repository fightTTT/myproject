// 矩形の当たり判定を表す構造体
typedef struct {
	float Left, Top, Right, Bottom;
} HIT;

// 複雑な当たり判定を表す構造体
#define MAX_HIT 32
typedef struct {
	HIT* Hit[MAX_HIT];  // 矩形の当たり判定
	int Num;            // 当たり判定の個数
} COMPLEX_HIT;

// 「矩形」対「矩形」の基本的な当たり判定処理
bool IsHit(HIT* a, HIT* b) {
	return
		a->Left<b->Right && b->Left<a->Right && 
		a->Top<b->Bottom && b->Top<a->Bottom;
}

// 「矩形」対「複雑な形」の当たり判定処理：
// 複数の矩形に対して順に当たり判定処理を行い，
// いずれかについて条件が成立したら「当たり」とする。
bool IsHit(COMPLEX_HIT* a, HIT* b) {
	for (int i=0; i<a->Num; i++) {
		if (IsHit(a->Hit[i], b)) return true;
	}
	return false;
}

// 「複雑な形」対「複雑な形」の当たり判定処理：
// 全ての組み合わせについて当たり判定処理を行い，
// いずれかの組み合わせで条件が成立したら「当たり」とする。
bool IsHit(COMPLEX_HIT* a, COMPLEX_HIT* b) {
	for (int i=0; i<a->Num; i++) {
		for (int j=0; j<b->Num; j++) {
			if (IsHit(a->Hit[i], b->Hit[j])) return true;
		}
	}
	return false;
}


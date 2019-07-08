#include<DxLib.h>
#include<cmath>
#include"Geometry.h"


using namespace std;

///カプセル形状の描画
void DrawCapsule(const Capsule& cap,unsigned int color) {
	DrawCircle(cap.posA.x, cap.posA.y, cap.radius, color);
	DrawCircle(cap.posB.x, cap.posB.y, cap.radius, color);

	auto v = cap.posB - cap.posA;
	auto angle = atan2(v.y, v.x)-DX_PI_F/2.0f;
	auto w = cos(angle)*cap.radius ;
	auto h = sin(angle)*cap.radius ;

	DrawQuadrangle(
		cap.posA.x - w, cap.posA.y - h,
		cap.posB.x - w, cap.posB.y - h,
		cap.posB.x + w, cap.posB.y + h,
		cap.posA.x + w, cap.posA.y + h, color, true);
}

///とある点を中心に回転して、その回転後の座標を返します。
///@param center 回転中心点
///@param angle 回転角度
///@param pos 元の座標
///@return 変換後の座標
Matrix RotatePosition(const Position2& center, float angle) {
	//①中心を原点に平行移動して
	//②原点中心に回転して
	//③中心を元の座標へ戻す

	Matrix mat = MultipleMat(TranslateMat(center.x, center.y),
		MultipleMat(RotateMat(angle),
			TranslateMat(-center.x, -center.y)));
	return mat;
	//これを書き換えて、特定の点を中心に回転を行うようにしてください。
}

Capsule RotateCapsule(Position2 center, float angle, const Capsule &cap) {
	Matrix mat = RotatePosition(Position2(center.x, center.y), angle);
	Capsule ret = cap;

	ret.posA = MultipleVec(mat, ret.posA);
	ret.posB = MultipleVec(mat, ret.posB);


	
	return ret;
}

//カプセルと円が当たったか？
bool IsHit(const Capsule& cap, const Circle& cc) {
	// cap,posAとposBが線分の端点
	// 手順
	// ①カプセルのposAとposBからLベクトル作る
	// ②カプセルのposAと円のposからTベクトルを作る
	// ③内積をとる
	// ④内積値に正規化LをかけてposAを足す→点M
	// ⑤点Mと円の中心posの距離を図る
	// ⑥cc.radius+cap.radiusと⑤で計算した距離を比較

	Position2 vecL =cap.posB - cap.posA;
	Position2 vecT = cc.pos - cap.posA;
	float dot = Dot(vecL, vecT) / Dot(vecL, vecL);

	dot = min(max(0.0f, dot), 1.0f);
	//Position2 pos = cap.posA + vecL * dot;
	Position2 M = { (cap.posA + vecL * dot) };
	float len = Vector2(cc.pos - M ).Magnitude();


	return (cc.radius + cap.radius > len);
	
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);

	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Circle c(50, Position2(50, 50));
	Capsule cap(20,Position2(100,200),Position2(300,200));

	char keystate[256];
	
	float angle = 0.0f;
	while (ProcessMessage() == 0) {
		ClearDrawScreen();

		int mx, my;
		GetMousePoint(&mx, &my);
		int minput = GetMouseInput();

		//カプセル回転
		if (minput&MOUSE_INPUT_LEFT) {
			angle = 0.1f;
		}
		else if (minput&MOUSE_INPUT_RIGHT) {
			angle = -0.1f;
		}
		else {
			angle = 0.0f;
		}

		GetHitKeyStateAll(keystate);

		//円うごく
		if (keystate[KEY_INPUT_RIGHT]) {
			c.pos.x = min(640, c.pos.x + 5);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			c.pos.x = max(0, c.pos.x -5);
		}
		if (keystate[KEY_INPUT_UP]) {
			c.pos.y = max(0, c.pos.y - 5);
		}
		else if (keystate[KEY_INPUT_DOWN]) {
			c.pos.y = min(480, c.pos.y + 5);
		}


		//カプセル形状をRotatePositionの結果の行列で回転させてください
		cap=RotateCapsule(Position2(mx, my), angle, cap);

		auto color = 0xffffff;
		if (IsHit(cap, c)) {
			color = 0xffaaaa;
		}

		DrawCircle(c.pos.x, c.pos.y, c.radius, color);
		DrawCapsule(cap, color);

		ScreenFlip();
	}

	DxLib_End();


}
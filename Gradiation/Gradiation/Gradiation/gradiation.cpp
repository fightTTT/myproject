#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

//一部の「あきらめてるガクセイさん」に告ぐ
//考えることを放棄するな。バカでもアホでもいいから考えることを放棄するな。
//考えることを放棄するような人はさ、それもう脳みそはいらなくない？
//ゾンビにでも食わせてあげたらいかがですか？

//定数
constexpr float _g = 0.3f;//重力加速度(1フレームに何ピクセル分動くか)
constexpr float shadow_offset = 3.0f;//影オフセット
constexpr float line_base = 460.0f;//床のベースライン
constexpr unsigned short circle_edge_num = 32;//円の辺の数


///ボールが線分と触れたもしくは線分より下に来たらtrueを返す
///@param seg 線分
///@param circle 円
///@remarks 垂線の長さを求めりゃいいと思うので外積使っても構いません
///関数crossは実装しているので…使ったらいかが？
bool IsHit(const Segment& seg, const Circle& circle) 
{
	Position2 vecL = seg.posb - seg.posa;
	Position2 vecT = circle.pos - seg.posa;
	float dot = Dot(vecL, vecT) / Dot(vecL, vecL);

	dot = min(max(0.0f, dot), 1.0f);
	Position2 M = { (seg.posa + vecL * dot) };
	float len = Vector2(circle.pos - M).Magnitude();


	return (circle.radius > len);
}

///現在の線分情報と指定のx座標から線分上のx座標でのy座標を返す
///@param seg 線分情報
///@param x X座標
///@return Y座標
float GetYFromSegmentAndX(const Segment& seg, const float x) {
	//「補間」もしくは「傾きとy=ax+b」について考えろ

	return  ((seg.posa.y - seg.posb.y) / (seg.posa.x - seg.posb.x))*x + seg.posa.y;
}

///線分から得られたY座標からボール(円)の補正座標を計算し返す
///@param c ボール(円)オブジェクト
///@param seg 線分オブジェクト
///@return あるべき円の中心座標
Position2 GetAdjustedCirclePosition(const Circle& c, const Segment& seg) {
	//「補間」もしくは「傾きとy=ax+b」について考えろ
	auto b = GetYFromSegmentAndX(seg, c.pos.x);

	return Position2(c.pos.x, b-c.radius);
}



///速度と加速度から新しい速度を得る
float GetNextVelocity(const float velocity,const float acceleration) {
	//簡単すぎるのでノーヒント
	return (velocity + acceleration);
}

///速度と角度からX方向とY方向の速度に分解し
///Vector2として返す
Vector2 GetVelocityVector(const float velocity, const float angle) {
	//どっちがcosでどっちがsinだ？
	return Vector2(velocity*cos(angle), velocity*sin(angle));
}

///線分の傾き方からボールの加速度を計算する
///@param seg 線分オブジェクト
///@return 現在の線分の傾きにおけるボールに対する加速度
///@remarks posAが左、posBが右とします。
float CalculateAccelerationForBall(const Segment& seg) {
	//①posA→posBへのベクトルを作る
	//②①のベクトルをもとにatanもしくはatan2を用いて角度を計算
	//③②で出した角度と重力加速度_gより加速度を計算する
	/*auto vec = atan2(seg.posb.y - seg.posa.y, seg.posb.x - seg.posa.x);

	GetVelocityVector(,vec)*/
	auto v = seg.posb - seg.posa;
	auto angle = atan2(v.y, v.x);
	return _g * sin(angle);

	//return _g * sin(vec);
}

///ぼかした影を表示
void DrawBlurShadow(int rendertarget,const Segment& seg,const Circle& c) {
	SetDrawScreen(rendertarget);
	ClearDrawScreen();
	
	int screen_width, screen_height;
	GetWindowSize(&screen_width, &screen_height);

	DrawBox(0, 0, screen_width, screen_height, 0xffffff, true);
	DrawCircleAA(c.pos.x + shadow_offset, c.pos.y + shadow_offset, c.radius, circle_edge_num, 0x444488, false, 3);
	DrawLineAA(seg.posa.x, seg.posa.y + shadow_offset, seg.posb.x, seg.posb.y + shadow_offset, 0x444488, 3);
	GraphFilter(rendertarget, DX_GRAPH_FILTER_GAUSS, 4, 800);
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, rendertarget, false);

}

void DrawBall(const Circle& c) {
	DrawCircleAA(c.pos.x + shadow_offset, c.pos.y + shadow_offset, c.radius, circle_edge_num, 0xaaaaaa, false, 2);
	DrawCircleAA(c.pos.x, c.pos.y, c.radius, circle_edge_num, 0x000000, false, 2);
}

void DrawFloor(const Segment& seg) {

	DrawLineAA(seg.posa.x, seg.posa.y+ shadow_offset, seg.posb.x, seg.posb.y+shadow_offset, 0xaaaaaa, 2);
	DrawLineAA(seg.posa.x, seg.posa.y , seg.posb.x, seg.posb.y , 0x000000, 2);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	int screen_width, screen_height;
	GetWindowSize(&screen_width, &screen_height);


	Segment seg(0,line_base, screen_width,line_base);
	Circle c(30, Position2(100, 100));
	
	
	char keystate[256];

	auto rt=MakeScreen(screen_width, screen_height);

	Vector2 _v = Vector2(0,_g);
	float vel = 0;
	while (ProcessMessage() == 0) {
		GetHitKeyStateAll(keystate);

		//床操作(上下移動のみ)
		if (keystate[KEY_INPUT_UP]) {
			if (seg.posb.y > line_base) {
				seg.posb.y += 1.0f;
			}
			else {
				seg.posa.y -= 1.0f;
			}
		}
		if (keystate[KEY_INPUT_DOWN]) {
			if (seg.posa.y < line_base) {
				seg.posa.y += 1.0f;
			}
			else {
				seg.posb.y -= 1.0f;
			}
		}



		//描画
		DrawBlurShadow(rt, seg, c);
		DrawBall(c);
		DrawFloor(seg);

		//画面端以上には行けないように
		if (seg.posa.x > c.pos.x || seg.posb.x < c.pos.x) {
			_v = Vector2(0, 0);
			vel = -vel*0.6;
			c.pos.x = min(seg.posb.x, max(seg.posa.x, c.pos.x));
		}

		//床に当たってなかったら重力による等加速直線運動
		//ただしこのままでは真下に落ちるだけなので
		//床に当たったら、坂道に沿って下るようにしてください
		if (IsHit(seg,c)) {
			//当たった場合は床に沿って進めてください。
			//上のほうに関数があるので、それを使ってください。
			float a = CalculateAccelerationForBall(seg);
			auto angle = atan2(seg.posb.y - seg.posa.y, seg.posb.x - seg.posa.x);
			vel = GetNextVelocity(vel, a);

			_v = GetVelocityVector(vel, angle);
			c.pos += _v;
			c.pos = GetAdjustedCirclePosition(c,seg);

			//DrawCircle(c.pos.x, c.pos.y, 0xff00ff, true, false);
			//DrawBox(0, 0, 200, 200, 0xff00ff, true);
		}
		else {
			_v.y += _g;
		}

		//ボールの等加速度直線運動を記述する
		c.pos += _v;
		
		ScreenFlip();
	}

	DxLib_End();
}

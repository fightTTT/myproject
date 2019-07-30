#include<DxLib.h>
#include<cmath>
#include<array>
#include"Geometry.h"

using namespace std;

//定数
constexpr float _g = 0.1f;//重力加速度(1フレームに何ピクセル分動くか)
constexpr float shadow_offset = 3.0f;//影オフセット
constexpr float line_base = 460.0f;//床のベースライン
constexpr unsigned short circle_edge_num = 32;//円の辺の数
constexpr int bowl_div_num = 10;//お椀分割数

///ボールが線分と触れたもしくは線分より下に来たらtrueを返す
///@param seg 線分
///@param circle 円
///@remarks 垂線の長さを求めりゃいいと思うので外積使っても構いません
///関数crossは実装しているので…使ったらいかが？
bool IsHit(const Segment& seg, const Circle& circle) {
	auto VA = circle.pos - seg.posa;
	auto VB = seg.posb - seg.posa;
	float len = VB.Magnitude();
	VB.Normalize();

	//内積出して、VBの長さを超えてたら当たってない…
	//どう計算しますか？
	if (0) {
		return abs(Cross(VA, VB)) < circle.radius;
	}
	else {
		return false;
	}
	
}


///線分の法線方向に「めり込まないように」補正します
///@param c ボール(円)オブジェクト
///@param seg 線分オブジェクト
///@return あるべき円の中心座標
Position2 GetAdjustedCirclePosition(const Circle& c, const Segment& seg) {
	auto VA = c.pos - seg.posa;
	auto VB = seg.posb - seg.posa;
	VB.Normalize();

	auto n = Vector2(VB.y, -VB.x);
	n.Normalize();

	//①内積から射影長を求めよ
	//②射影長から射影点を求めよ
	//③円の現在座標と射影点から垂線ベクトルを求めよ
	//④③方向に半径ぶん遠ざけた座標を返そう


	float shadowLen = Dot(VA,VB);//射影長
	Position2 shadowPos = Position2();//射影座標
	auto V = Vector2();//垂線ベクトル


	
	return Position2();//円の、あるべき座標を返してください
}

///線分の傾き方からボールの加速度を計算する
///@param seg 線分オブジェクト
///@return 現在の線分の傾きにおけるボールに対する加速度
///@remarks posAが左、posBが右とします。
float CalculateAccelerationForBall(const Segment& seg) {
	//①posA→posBへのベクトルを作る
	auto v = seg.posb - seg.posa;
	//②①のベクトルをもとにatanもしくはatan2を用いて角度を計算
	auto angle = atan2(v.y,v.x);
	//③②で出した角度と重力加速度_gより加速度を計算する
	return _g * sin(angle);
}

///速度と加速度から新しい速度を得る
float GetNextVelocity(const float velocity,const float acceleration) {
	return velocity + acceleration;
}

///速度と角度からX方向とY方向の速度に分解し
///Vector2として返す
Vector2 GetVelocityVector(const float velocity, const float angle) {
	return Vector2(cos(angle), sin(angle))*velocity;
}



///ぼかした影を表示
void DrawBlurShadow(int rendertarget,array< Segment , bowl_div_num>segs,const Circle& c) {
	SetDrawScreen(rendertarget);
	ClearDrawScreen();
	
	int screen_width, screen_height;
	GetWindowSize(&screen_width, &screen_height);

	DrawBox(0, 0, screen_width, screen_height, 0xffffff, true);
	DrawCircleAA(c.pos.x + shadow_offset, c.pos.y + shadow_offset, c.radius, circle_edge_num, 0x444488, false, 3);
	for (auto& seg : segs) {
		DrawLineAA(seg.posa.x, seg.posa.y + shadow_offset, seg.posb.x, seg.posb.y + shadow_offset, 0x444488, 3);
	}
	GraphFilter(rendertarget, DX_GRAPH_FILTER_GAUSS, 4, 800);
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, rendertarget, false);

}

void DrawBall(const Circle& c) {
	DrawCircleAA(c.pos.x + shadow_offset, c.pos.y + shadow_offset, c.radius, circle_edge_num, 0xaaaaaa, false, 2);
	DrawCircleAA(c.pos.x, c.pos.y, c.radius, circle_edge_num, 0x000000, false, 2);
}

void DrawFloor(const array<Segment, bowl_div_num>& segs) {

	for (auto& seg : segs) {
		DrawLineAA(seg.posa.x, seg.posa.y + shadow_offset, seg.posb.x, seg.posb.y + shadow_offset, 0xaaaaaa, 2);
		DrawLineAA(seg.posa.x, seg.posa.y, seg.posb.x, seg.posb.y, 0x000000, 2);
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	int screen_width, screen_height;
	GetWindowSize(&screen_width, &screen_height);

	
	const auto div_angle = (DX_PI_F*1.02f) / (float)bowl_div_num;
	array<Segment, bowl_div_num> segs;
	float theta = 0;
	float radius = screen_width / 2.0f;
	for (auto& seg:segs) {
		seg.posa.x = radius-cos(theta)*radius;
		seg.posa.y = line_base-radius+sin(theta)*radius;
		seg.posb.x = radius-cos(theta+div_angle)*radius;
		seg.posb.y = line_base - radius + sin(theta + div_angle)*radius;
		theta += div_angle;
	}
	Circle c(30, Position2(32, 132));
	
	
	char keystate[256];

	auto rt=MakeScreen(screen_width, screen_height);

	Vector2 _v = Vector2(0,_g);
	float v = 0;
	while (ProcessMessage() == 0) {
		GetHitKeyStateAll(keystate);

		
		//描画
		DrawBlurShadow(rt, segs, c);
		DrawBall(c);
		DrawFloor(segs);


		
		bool isHit = false;
		for (auto& seg : segs) {
			//床に当たってなかったら重力による等加速直線運動
			//ただしこのままでは真下に落ちるだけなので
			//床に当たったら、坂道に沿って下るようにしてください
			if (IsHit(seg, c)) {
				isHit = true;
				//当たった場合は床に沿って進めてください。
				//上のほうに関数があるので、それを使ってください。
				auto a = CalculateAccelerationForBall(seg);
				v = GetNextVelocity(v, a);
				auto vec = seg.posb - seg.posa;
				auto angle = atan2(vec.y, vec.x);
				_v = GetVelocityVector(v, angle);
				c.pos += _v;
				c.pos = GetAdjustedCirclePosition(c, seg);
				break;
			}
		}
		if(!isHit) {
			_v.y += _g;
			c.pos += _v;
		}
		//ボールの等加速度直線運動を記述する
		
		ScreenFlip();
	}

	DxLib_End();
}

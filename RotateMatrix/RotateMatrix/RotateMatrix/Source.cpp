#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

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

int WINAPI WinMain(HINSTANCE , HINSTANCE, LPSTR,int) {
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	/*Matrix m = RotateMat(90 * DX_PI / 180);
	Position2 pos = { 100,100 };
	pos = MultipleVec(m, pos);*/

	Position2 positions[4] = {
		{100,100},//左上
		{200,100},//右上
		{200,200},//右下
		{100,200},//左下
	};

	float angle = 0.0f;
	while (ProcessMessage()==0) {
		ClearDrawScreen();

		int mx, my;
		GetMousePoint(&mx, &my);

		int minput = GetMouseInput();

		if (minput&MOUSE_INPUT_LEFT) {
			angle = 0.1f;
		}
		else if (minput&MOUSE_INPUT_RIGHT) {
			angle = -0.1f;
		}
		else {
			angle = 0.0f;
		}

		Matrix mat = RotatePosition(Position2(mx, my), angle);

		//それぞれの頂点に回転変換を施す
		for (auto& pos : positions) {
			pos = MultipleVec(mat, pos);
			/*pos = RotatePosition(Position2(mx, my), angle, pos);*/
		}

		DrawQuadrangleAA(
			positions[0].x,positions[0].y,
			positions[1].x, positions[1].y,
			positions[2].x, positions[2].y, 
			positions[3].x, positions[3].y, 
			0xffffff,true);
		ScreenFlip();
	}
	DxLib_End();
}
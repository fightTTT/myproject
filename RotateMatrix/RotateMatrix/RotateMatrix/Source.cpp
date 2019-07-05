#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

///�Ƃ���_�𒆐S�ɉ�]���āA���̉�]��̍��W��Ԃ��܂��B
///@param center ��]���S�_
///@param angle ��]�p�x
///@param pos ���̍��W
///@return �ϊ���̍��W
Matrix RotatePosition(const Position2& center, float angle) {
	//�@���S�����_�ɕ��s�ړ�����
	//�A���_���S�ɉ�]����
	//�B���S�����̍��W�֖߂�

	Matrix mat = MultipleMat(TranslateMat(center.x, center.y),
							MultipleMat(RotateMat(angle),
								TranslateMat(-center.x, -center.y)));

	return mat;
	//��������������āA����̓_�𒆐S�ɉ�]���s���悤�ɂ��Ă��������B
}

int WINAPI WinMain(HINSTANCE , HINSTANCE, LPSTR,int) {
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	/*Matrix m = RotateMat(90 * DX_PI / 180);
	Position2 pos = { 100,100 };
	pos = MultipleVec(m, pos);*/

	Position2 positions[4] = {
		{100,100},//����
		{200,100},//�E��
		{200,200},//�E��
		{100,200},//����
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

		//���ꂼ��̒��_�ɉ�]�ϊ����{��
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
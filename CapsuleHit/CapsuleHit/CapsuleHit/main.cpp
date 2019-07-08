#include<DxLib.h>
#include<cmath>
#include"Geometry.h"


using namespace std;

///�J�v�Z���`��̕`��
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

Capsule RotateCapsule(Position2 center, float angle, const Capsule &cap) {
	Matrix mat = RotatePosition(Position2(center.x, center.y), angle);
	Capsule ret = cap;

	ret.posA = MultipleVec(mat, ret.posA);
	ret.posB = MultipleVec(mat, ret.posB);


	
	return ret;
}

//�J�v�Z���Ɖ~�������������H
bool IsHit(const Capsule& cap, const Circle& cc) {
	// cap,posA��posB�������̒[�_
	// �菇
	// �@�J�v�Z����posA��posB����L�x�N�g�����
	// �A�J�v�Z����posA�Ɖ~��pos����T�x�N�g�������
	// �B���ς��Ƃ�
	// �C���ϒl�ɐ��K��L��������posA�𑫂����_M
	// �D�_M�Ɖ~�̒��Spos�̋�����}��
	// �Ecc.radius+cap.radius�ƇD�Ōv�Z�����������r

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

		//�J�v�Z����]
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

		//�~������
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


		//�J�v�Z���`���RotatePosition�̌��ʂ̍s��ŉ�]�����Ă�������
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
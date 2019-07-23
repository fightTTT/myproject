#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

//�ꕔ�́u������߂Ă�K�N�Z�C����v�ɍ���
//�l���邱�Ƃ��������ȁB�o�J�ł��A�z�ł���������l���邱�Ƃ��������ȁB
//�l���邱�Ƃ��������悤�Ȑl�͂��A��������]�݂��͂���Ȃ��Ȃ��H
//�]���r�ɂł��H�킹�Ă������炢�����ł����H

//�萔
constexpr float _g = 0.3f;//�d�͉����x(1�t���[���ɉ��s�N�Z����������)
constexpr float shadow_offset = 3.0f;//�e�I�t�Z�b�g
constexpr float line_base = 460.0f;//���̃x�[�X���C��
constexpr unsigned short circle_edge_num = 32;//�~�̕ӂ̐�


///�{�[���������ƐG�ꂽ�������͐�����艺�ɗ�����true��Ԃ�
///@param seg ����
///@param circle �~
///@remarks �����̒��������߂�Ⴂ���Ǝv���̂ŊO�ώg���Ă��\���܂���
///�֐�cross�͎������Ă���̂Łc�g�����炢�����H
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

///���݂̐������Ǝw���x���W����������x���W�ł�y���W��Ԃ�
///@param seg �������
///@param x X���W
///@return Y���W
float GetYFromSegmentAndX(const Segment& seg, const float x) {
	//�u��ԁv�������́u�X����y=ax+b�v�ɂ��čl����

	return  ((seg.posa.y - seg.posb.y) / (seg.posa.x - seg.posb.x))*x + seg.posa.y;
}

///�������瓾��ꂽY���W����{�[��(�~)�̕␳���W���v�Z���Ԃ�
///@param c �{�[��(�~)�I�u�W�F�N�g
///@param seg �����I�u�W�F�N�g
///@return ����ׂ��~�̒��S���W
Position2 GetAdjustedCirclePosition(const Circle& c, const Segment& seg) {
	//�u��ԁv�������́u�X����y=ax+b�v�ɂ��čl����
	auto b = GetYFromSegmentAndX(seg, c.pos.x);

	return Position2(c.pos.x, b-c.radius);
}



///���x�Ɖ����x����V�������x�𓾂�
float GetNextVelocity(const float velocity,const float acceleration) {
	//�ȒP������̂Ńm�[�q���g
	return (velocity + acceleration);
}

///���x�Ɗp�x����X������Y�����̑��x�ɕ�����
///Vector2�Ƃ��ĕԂ�
Vector2 GetVelocityVector(const float velocity, const float angle) {
	//�ǂ�����cos�łǂ�����sin���H
	return Vector2(velocity*cos(angle), velocity*sin(angle));
}

///�����̌X��������{�[���̉����x���v�Z����
///@param seg �����I�u�W�F�N�g
///@return ���݂̐����̌X���ɂ�����{�[���ɑ΂�������x
///@remarks posA�����AposB���E�Ƃ��܂��B
float CalculateAccelerationForBall(const Segment& seg) {
	//�@posA��posB�ւ̃x�N�g�������
	//�A�@�̃x�N�g�������Ƃ�atan��������atan2��p���Ċp�x���v�Z
	//�B�A�ŏo�����p�x�Əd�͉����x_g�������x���v�Z����
	/*auto vec = atan2(seg.posb.y - seg.posa.y, seg.posb.x - seg.posa.x);

	GetVelocityVector(,vec)*/
	auto v = seg.posb - seg.posa;
	auto angle = atan2(v.y, v.x);
	return _g * sin(angle);

	//return _g * sin(vec);
}

///�ڂ������e��\��
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

		//������(�㉺�ړ��̂�)
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



		//�`��
		DrawBlurShadow(rt, seg, c);
		DrawBall(c);
		DrawFloor(seg);

		//��ʒ[�ȏ�ɂ͍s���Ȃ��悤��
		if (seg.posa.x > c.pos.x || seg.posb.x < c.pos.x) {
			_v = Vector2(0, 0);
			vel = -vel*0.6;
			c.pos.x = min(seg.posb.x, max(seg.posa.x, c.pos.x));
		}

		//���ɓ������ĂȂ�������d�͂ɂ�铙���������^��
		//���������̂܂܂ł͐^���ɗ����邾���Ȃ̂�
		//���ɓ���������A�⓹�ɉ����ĉ���悤�ɂ��Ă�������
		if (IsHit(seg,c)) {
			//���������ꍇ�͏��ɉ����Đi�߂Ă��������B
			//��̂ق��Ɋ֐�������̂ŁA������g���Ă��������B
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

		//�{�[���̓������x�����^�����L�q����
		c.pos += _v;
		
		ScreenFlip();
	}

	DxLib_End();
}

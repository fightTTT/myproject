#include<DxLib.h>
#include<cmath>
#include<array>
#include"Geometry.h"

using namespace std;

//�萔
constexpr float _g = 0.1f;//�d�͉����x(1�t���[���ɉ��s�N�Z����������)
constexpr float shadow_offset = 3.0f;//�e�I�t�Z�b�g
constexpr float line_base = 460.0f;//���̃x�[�X���C��
constexpr unsigned short circle_edge_num = 32;//�~�̕ӂ̐�
constexpr int bowl_div_num = 10;//���o������

///�{�[���������ƐG�ꂽ�������͐�����艺�ɗ�����true��Ԃ�
///@param seg ����
///@param circle �~
///@remarks �����̒��������߂�Ⴂ���Ǝv���̂ŊO�ώg���Ă��\���܂���
///�֐�cross�͎������Ă���̂Łc�g�����炢�����H
bool IsHit(const Segment& seg, const Circle& circle) {
	auto VA = circle.pos - seg.posa;
	auto VB = seg.posb - seg.posa;
	float len = VB.Magnitude();
	VB.Normalize();

	//���Ϗo���āAVB�̒����𒴂��Ă��瓖�����ĂȂ��c
	//�ǂ��v�Z���܂����H
	if (0) {
		return abs(Cross(VA, VB)) < circle.radius;
	}
	else {
		return false;
	}
	
}


///�����̖@�������Ɂu�߂荞�܂Ȃ��悤�Ɂv�␳���܂�
///@param c �{�[��(�~)�I�u�W�F�N�g
///@param seg �����I�u�W�F�N�g
///@return ����ׂ��~�̒��S���W
Position2 GetAdjustedCirclePosition(const Circle& c, const Segment& seg) {
	auto VA = c.pos - seg.posa;
	auto VB = seg.posb - seg.posa;
	VB.Normalize();

	auto n = Vector2(VB.y, -VB.x);
	n.Normalize();

	//�@���ς���ˉe�������߂�
	//�A�ˉe������ˉe�_�����߂�
	//�B�~�̌��ݍ��W�Ǝˉe�_���琂���x�N�g�������߂�
	//�C�B�����ɔ��a�Ԃ񉓂��������W��Ԃ���


	float shadowLen = Dot(VA,VB);//�ˉe��
	Position2 shadowPos = Position2();//�ˉe���W
	auto V = Vector2();//�����x�N�g��


	
	return Position2();//�~�́A����ׂ����W��Ԃ��Ă�������
}

///�����̌X��������{�[���̉����x���v�Z����
///@param seg �����I�u�W�F�N�g
///@return ���݂̐����̌X���ɂ�����{�[���ɑ΂�������x
///@remarks posA�����AposB���E�Ƃ��܂��B
float CalculateAccelerationForBall(const Segment& seg) {
	//�@posA��posB�ւ̃x�N�g�������
	auto v = seg.posb - seg.posa;
	//�A�@�̃x�N�g�������Ƃ�atan��������atan2��p���Ċp�x���v�Z
	auto angle = atan2(v.y,v.x);
	//�B�A�ŏo�����p�x�Əd�͉����x_g�������x���v�Z����
	return _g * sin(angle);
}

///���x�Ɖ����x����V�������x�𓾂�
float GetNextVelocity(const float velocity,const float acceleration) {
	return velocity + acceleration;
}

///���x�Ɗp�x����X������Y�����̑��x�ɕ�����
///Vector2�Ƃ��ĕԂ�
Vector2 GetVelocityVector(const float velocity, const float angle) {
	return Vector2(cos(angle), sin(angle))*velocity;
}



///�ڂ������e��\��
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

		
		//�`��
		DrawBlurShadow(rt, segs, c);
		DrawBall(c);
		DrawFloor(segs);


		
		bool isHit = false;
		for (auto& seg : segs) {
			//���ɓ������ĂȂ�������d�͂ɂ�铙���������^��
			//���������̂܂܂ł͐^���ɗ����邾���Ȃ̂�
			//���ɓ���������A�⓹�ɉ����ĉ���悤�ɂ��Ă�������
			if (IsHit(seg, c)) {
				isHit = true;
				//���������ꍇ�͏��ɉ����Đi�߂Ă��������B
				//��̂ق��Ɋ֐�������̂ŁA������g���Ă��������B
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
		//�{�[���̓������x�����^�����L�q����
		
		ScreenFlip();
	}

	DxLib_End();
}

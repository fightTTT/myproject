#include "Bullet.h"
#include <_Debug/_DebugConOut.h>

Bullet::Bullet()
{
	Init();
}

Bullet::Bullet(Vector2Dbl pos)
{
	// ���x
	_speed = { 0,5 };

	// �傫��
	_size = { 3,4 };

	// �������p�֐�
	Init();

	// �����p�׸ޡ������false(�e��\��)
	_alive = false;
}


Bullet::~Bullet()
{
}

void Bullet::Draw(void)
{
}

void Bullet::UpDate(void)
{
	// �e�͉�ʏ㕔�Ɍ������Ĕ��
	_pos.y-= _speed.y;

	// ��ʊO����
	if (_pos.y + (_size.y / 2) < 0)
	{
		// �׸ނ�false��(��\��)
		_actFlg = false;
	}
}

UNIT Bullet::GetUnitType(void)
{
	return UNIT::P_Blt;
}

void Bullet::SetactFlg(Vector2Dbl pos)
{
	// ���˂������W
	_pos = pos;

	// �\������
	_actFlg = true;
}

void Bullet::SetactFlg(void)
{
	_actFlg = false;
}

void Bullet::Init(void)
{
	// ��Ұ��ݓo�^
	AnimVector data;
	data.reserve(1);

	// ��׸���摜
	data.emplace_back(IMAGE_ID("�e")[0], 0);
	
	// ɰ�قɓo�^
	SetAnim(ANIM::NORMAL, data);

	// ���ޯ�����޳
	TRASE("%d:%d\n", _pos.x, _pos.y);
}

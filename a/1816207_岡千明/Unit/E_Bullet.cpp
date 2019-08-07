#include "E_Bullet.h"
#include <Scene/SceneMng.h>

E_Bullet::E_Bullet()
{
	// �������p�֐�
	Init();
}

E_Bullet::E_Bullet(Vector2Dbl pos)
{
	// ���x
	_speed = { 0,2 };

	// �傫��
	_size = { 3,4 };

	// �������p�֐�
	Init();

	// �����p�׸ޡ������false(�e��\��)
	_alive = false;

	_angle = DX_PI;
}


E_Bullet::~E_Bullet()
{
}

void E_Bullet::Draw(void)
{
}

void E_Bullet::UpDate(void)
{
	// �e�͉�ʉ��Ɍ������Ĕ��
	_pos.y += _speed.y;

	// ��ʊO����
	if (lpSceneMng.gameScreenSize.y < _pos.y + (_size.y / 2))
	{
		// �׸ނ�false��(��\��)
		_actFlg = false;
	}
}

UNIT E_Bullet::GetUnitType(void)
{
	return UNIT::E_Blt;
}

void E_Bullet::SetactFlg(Vector2Dbl pos)
{
	// ���˂������W
	_pos = pos;

	// �\������
	_actFlg = true;
}

void E_Bullet::SetactFlg(void)
{
	_actFlg = false;
}

void E_Bullet::Init(void)
{
	// ��Ұ��ݓo�^
	AnimVector data;
	data.reserve(1);

	// ��׸���摜
	data.emplace_back(IMAGE_ID("�e")[1], 0);

	// ɰ�قɓo�^
	SetAnim(ANIM::NORMAL, data);

}

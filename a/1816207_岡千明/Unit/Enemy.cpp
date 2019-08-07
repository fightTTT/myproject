#include <math.h>
#include <DxLib.h>
#include "Enemy.h"
#include <_Debug/_DebugDispOut.h>
#include <Scene/SceneMng.h>
#include <Scene/GameScene.h>
#include <Public/ScoreMng.h>
#include <Public/SoundMng.h>

Enemy::Enemy()
{
}

Enemy::Enemy(Vector2 pos)
{
	// ���W
	_pos.x = pos.x;
	_pos.y = pos.y;

	// �������p�֐�
	//Init();
	move = &Enemy::Sigmoid;
}

Enemy::Enemy(Enemy_State state)
{
	// ���W
	_pos = std::get<static_cast<int>(Enemy_State_ID::POS)>(state);

	// �������W
	_startPos = _pos;

	// ���
	_type = std::get<static_cast<int>(Enemy_State_ID::TYPE)>(state);

	// �傫��
	_size = std::get<static_cast<int>(Enemy_State_ID::SIZE)>(state);

	// �����̈ړ�
	_moveCnt = static_cast<int>(MOVE_TYPE::SIGMOID);

	// �ړI�n
	_aim = std::get<static_cast<int>(Enemy_State_ID::AIM)>(state);

	// ��߰��
	_speed = { 2.0,2.0 };

	// �I�_����n�_�������Ďc��̋������o��(���Ӳ�ޗp)
	_len = _aim[_moveCnt].first - _startPos;

	// ���a(�~�^���p)
	_rad = 0;

	_secSigFlag = false;

	// ���Ӳ�ޗp
	_cnt = -10;

	// ���E�ړ��ڍs�׸�
	_lrFlag = false;

	_centerPos.x = lpSceneMng.gameScreenSize.x / 2;
	_centerPos.y = -500;

	// HP�ƽ���̐ݒ�
	if (_type == ENEMY_TYPE::A)
	{
		_score = 100;

		_hp = 1;
	}
	else if (_type == ENEMY_TYPE::B)
	{
		_score = 400;
	
		_hp = 1;
	}
	else if (_type == ENEMY_TYPE::C)
	{
		_score = 1000;
		_hp = 2;
	}

	_oldHp = _hp;

	// �e����
	_e_Bullet_vec.reserve(1);

	_e_Bullet_vec.emplace_back(std::make_shared<E_Bullet>(_pos));
	std::get<4>(state).emplace_back(_e_Bullet_vec[0]);

	// SE�̓o�^
	// �e
	lpSoundMng.SoundInit("sound/E_Bullet.mp3", "��а��گ�");
	// ��Ұ��
	lpSoundMng.SoundInit("sound/Damage.mp3", "��Ұ��");
	// ���S��
	lpSoundMng.SoundInit("sound/E_Destroy.mp3", "��а���S");
	
	// �֐��߲��������l(���Ӳ�ނɈڍs)
	move = &Enemy::Sigmoid;

	// �������p�֐�
	Init();
}

Enemy::~Enemy()
{
}

void Enemy::Draw(void)
{
}

void Enemy::UpDate(void)
{
	// ���S����return�ŕԂ�
	if (DestroyPlock())
	{
		return;
	}

	if (lpSceneMng.cnt() % 120 < 60)
	{
		_gameCnt = lpSceneMng.cnt() % 120;
	}
	else
	{
		_gameCnt = 119 - (lpSceneMng.cnt() % 120);
	}

	if (_shotFlag)
	{
		if(_e_Bullet_vec[0]->actFlg()!=true)
		{
			if (rand() % 300 == 0)
			{
				_e_Bullet_vec[0]->SetactFlg(_pos);
				lpSoundMng.SetSound("��а��گ�");
			}
		}
	}

	// �ðĈێ�
	(this->*move)();

	// ���S��
	if (_hp <= 0)
	{
		// ����̉��Z
		lpScoreMng.AddScore(_score);

		if (_alive)
		{
			_alive = false;

			// SE
			lpSoundMng.SetSound("��а���S");
		}
		// �����摜�ɍ����ւ�
		animKey(ANIM::DEATH);
	}
	else if (_oldHp > _hp)
	{
		// �޽�����Ȃ��Ұ��݂ɕύX
		animKey(ANIM::EX);
		// ��Ұ��ݗp���Ă̾��
		SetAnimCnt();

		// SE
		lpSoundMng.SetSound("��Ұ��");
		_oldHp = _hp;
	}

	//// ���ޯ��p
	//_DebugDrawBox(_pos.x - _size.x / 2, _pos.y - _size.x / 2, _pos.x + _size.x / 2, _pos.y + _size.x / 2, 0xff4500, true);
}
// _alive��ture
// _alive��false�ɂȂ�����true�̏����͂��Ȃ��Adeath��true�ɂȂ邽�߂̏������s��
// _death = false�̎��͎��񂾱�Ұ��ݏI�������true

UNIT Enemy::GetUnitType(void)
{
	return UNIT::ENEMY;
}

bool Enemy::Init(void)
{
	// ��Ұ��ݓo�^
	AnimVector data;
	data.reserve(2);

	// ��׸���摜
	data.emplace_back(IMAGE_ID("���")[10 + (static_cast<int>(_type) * 10)], 30);
	data.emplace_back(IMAGE_ID("���")[11 + (static_cast<int>(_type) * 10)], 60);

	// _animMap�ɓo�^(�ʏ�摜��NOMAL�w��)
	SetAnim(ANIM::NORMAL, data);

	// �̈��ύX
	data.reserve(1);
	data.emplace_back(IMAGE_ID("���")[34], 30);
	data.emplace_back(IMAGE_ID("���")[35], 60);
	// EX�ɓo�^
	SetAnim(ANIM::EX, data);

	// �����p�ɗ̈��ύX
	data.reserve(5);

	for (int k = 0; k < 5; k++)
	{
		// �����p�摜
		data.emplace_back(IMAGE_ID("�G����")[k], 5 + (k * 5));

		if (k == 4)
		{
			// �ݼ��ėp
			data.emplace_back(-1, 5 + ((k + 1) * 5));
		}
	}
	// ������EX�Ɏw��
	SetAnim(ANIM::DEATH, data);

	// ��Ұ��ݗp���Ă̾��
	SetAnimCnt();

	return true;
}

void Enemy::SetAnimCnt(void)
{
	_animCount = lpSceneMng.cnt() % LastAnimCnt();
}

void Enemy::Sigmoid()
{
	auto X = ((_cnt + 10) / 20);
	auto Y = 1.0 / (1.0 + exp(-1.0 * _cnt));

	// 1�ڰёO�̍��W(��Ұ��݂̌����p)
	auto oldPos = _pos;

	// �ړ�
	_pos.x = X * _len.x + _startPos.x;
	_pos.y = Y * _len.y + _startPos.y;

	// ��Ұ��݂̌���
	_angle = atan2(_pos.y - oldPos.y, _pos.x - oldPos.x) + 90 * DX_PI / 180;

	if (round(_pos.x) == round(_aim[_moveCnt].first.x))
	{
		_cnt = 0;

		_moveCnt = static_cast<int>(MOVE_TYPE::SPIRAL);

		// ���a
		_rad = hypot(_aim[_moveCnt].first.x - _pos.x, _aim[_moveCnt].first.y - _pos.y);

		// ���a
		_diameter = _rad * 2;

		// �p�x
		_radian = atan2(_aim[_moveCnt].first.y - _pos.y, _aim[_moveCnt].first.x - _pos.x);

		// ���̈ړ��֐���
		move = &Enemy::Spiral;
	}

	if (_cnt < 10)
	{
		_cnt += 0.2;
	}

}

void Enemy::Spiral(void)
{
	// 1�ڰёO�̍��W(��Ұ��݂̌����p)
	auto oldPos = _pos;

	// �����ɍ�����o�����Ă��ꍇ
	if (_startPos.x < 0)
	{
		// �ړ�(�����)
		_pos.x = _aim[_moveCnt].first.x + cos(_radian) * _rad + _diameter;
		_pos.y = _aim[_moveCnt].first.y + sin(_radian) * -_rad;
	}
	// �E���痈�Ă����ꍇ
	else
	{
		// �ړ�(�E���)
		_pos.x = _aim[_moveCnt].first.x + _rad * -cos(_radian);
		_pos.y = _aim[_moveCnt].first.y + _rad * -sin(_radian);
	}

	// ��Ұ��݂̌���
	_angle = atan2(_pos.y - oldPos.y, _pos.x - oldPos.x) + 90 * DX_PI / 180;

	// ���a�����ʏ������Ȃ�����
	if (_rad < 20)
	{
		_moveCnt = static_cast<int>(MOVE_TYPE::MOVE_LR);

		// ���̈ړ��֐���
		move = &Enemy::MoveLR;
	}

	// �~�̑傫����ς��Ă���
	_radian += 0.1;
	_rad--;

}

void Enemy::MoveLR(void)
{
	//// ���S���W���玩����pos�܂ł��޸��
	//Vector2Dbl a = _pos - _centerPos;

	//// ���K��
	//Vector2Dbl i = a / hypot(_pos.y, _pos.x);

	// �޸��
	Vector2Dbl i = _aim[_moveCnt].first - _centerPos;
	// ���K��
	Vector2Dbl k = i / hypot(i.x, i.y);
	k.y = k.y / 3;

	if (_lrFlag)
	{
		_pos.x = _aim[_moveCnt].first.x + k.x * _gameCnt;
		_pos.y = _aim[_moveCnt].first.y + k.y * _gameCnt;

		_shotFlag = true;
	}
	else if (_pos != _aim[_moveCnt].first)
	{

		// �ړI�n�܂ł̋������o��
		float	_ang = atan2(_aim[_moveCnt].first.y - _pos.y, _aim[_moveCnt].first.x - _pos.x);

		// ��߰�ނ̐ݒ�
		_speed.x = cos(_ang) * 10;
		_speed.y = sin(_ang) * 10;

		// �ړI�n�܂�
		if ((abs(_aim[_moveCnt].first.x - _pos.x) > abs(_speed.x)) && (abs(_aim[_moveCnt].first.y - _pos.y) > abs(_speed.y)))
		{
			// ��Ұ��݂̌���
			_angle = atan2(_aim[_moveCnt].first.y - _pos.y, _aim[_moveCnt].first.x - _pos.x) + 90 * DX_PI / 180;

			// �ړ�
			_pos += _speed;
		}
		else
		{
			// ����Ă��炻�낦��
			_speed = _aim[_moveCnt].first - _pos;
			_pos += _speed;

			// �ڕW�n�_�ɓ��B���Ă�̂ō��E�ړ��Ɉڍs
			_lrFlag = true;

			// ��Ұ��݂̌���
			_angle = 0;
		}
	}


}

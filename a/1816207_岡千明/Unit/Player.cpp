#include <DxLib.h>
#include "Player.h"
#include <Input/KeyState.h>
#include <Unit/Bullet.h>
#include <Scene/SceneMng.h>
#include <_Debug/_DebugConOut.h>
#include <_Debug/_DebugDispOut.h>
#include <Public/SoundMng.h>

Player::Player()
{
}

Player::Player(Vector2 pos)
{
	// ���W
	_pos.x = pos.x;
	_pos.y = pos.y;

	// �傫��
	_size.x = 30;
	_size.y = 32;

	// ���x
	_speed = { 5,5 };

	// ���ޯ�����޳
	TRASE("%d:%d\n", pos.x, pos.y);

	// ���۰װ�׽����
	_input = std::make_unique<KeyState>();

	// �������֐�
	Init();
}

Player::Player(Vector2 pos, std::list<std::shared_ptr<Bullet>>& list)
{
	// ���W
	_pos.x = pos.x;
	_pos.y = pos.y;

	// �傫��
	_size.x = 30;
	_size.y = 32;

	// ���x
	_speed = { 5,5 };

	// �̗�
	_hp = 3;
	_oldHp = _hp;

	//// ���ޯ�����޳
	//TRASE("%d:%d\n", pos.x, pos.y);

	// ���۰װ�׽����
	_input = std::make_unique<KeyState>();

	// �e����
	_bullet_vec.reserve(2);
	for (int k = 0; k < 2; k++)
	{
		// 2���܂ŏo����悤�ɂ���
		_bullet_vec.emplace_back(std::make_shared<Bullet>(_pos));

		// GameScene�̒e�pؽĂɂ����
		list.emplace_back(_bullet_vec[k]);
	}

	// �������֐�
	Init();
}


Player::~Player()
{
}

void Player::Draw(void)
{
	DrawGraph(_pos.x, _pos.y,
		ImageMng::GetInstance().GetID("���")[0],
		true);
}

void Player::UpDate(void)
{
	// ���S����return�ŕԂ�
	if (DestroyPlock())
	{
		return;
	}

	// �����͂̏�ԍX�V
	_input->UpDate();

	// ��ڲ԰�̈ړ�(���E�̂�)
	int TmpPos = _pos.x;
	// ���ړ�
	if (_input->state(INPUT_ID::LEFT).first)
	{
		TmpPos -= _speed.x;
		// ��ʊO�ɏo��ꍇ
		if (_size.x / 2 > TmpPos)
		{
			// �␳
			TmpPos = _size.x / 2;
		}
	}
	// �E�ړ�
	if (_input->state(INPUT_ID::RIGHT).first)
	{
		TmpPos += _speed.x;
		// ��ʊO�ɏo��ꍇ
		if (TmpPos > lpSceneMng.gameScreenSize.x - (_size.x / 2))
		{
			// �␳
			TmpPos = lpSceneMng.gameScreenSize.x - (_size.x / 2);
		}
	}
	// �����ňړ�
	_pos.x = TmpPos;

	// �e����(Z��)
	if (_input->state(INPUT_ID::BTN_1).first && !(_input->state(INPUT_ID::BTN_1).second))
	{
		for (int k = 0; k < 2; k++)
		{
			// ��è�ނłȂ��e��T��
			if (_bullet_vec[k]->actFlg() != true)
			{
				// �e��flag��true�ɂ��ďo��
				_bullet_vec[k]->SetactFlg(_pos);

				// SE�Đ�
				lpSoundMng.SetSound("��ڲ԰��گ�");

				break;
			}
		}
	}

	//if ()
	//{

	//}
	// ���S��
	else if (_hp <= 0)
	{
		if (_alive)
		{
			// SE�Đ�
			lpSoundMng.SetSound("��ڲ԰���S");
			_alive = false;
		}
		// �����摜�ɍ����ւ�
		animKey(ANIM::DEATH);
	}
	// ��Ұ�ގ�
	else if (_oldHp > _hp)
	{
		// SE
		lpSoundMng.SetSound("��Ұ��");
		_oldHp = _hp;
	}
	// ���ޯ��p
	//_DebugDrawBox(_pos.x - _size.x / 2, _pos.y - _size.x / 2, _pos.x + _size.x / 2, _pos.y + _size.x / 2, 0x00fa9a, true);
	//_DebugDrawFormatString(0, 0, 0x00fa9a,"%d:%d", _pos.x, _pos.y);
}

UNIT Player::GetUnitType(void)
{
	return UNIT::PLAYER;
}

bool Player::Init(void)
{
	// ��Ұ��ݓo�^
	AnimVector data;
	data.reserve(2);

	// ��׸���摜
	data.emplace_back(IMAGE_ID("���")[0], 30);
	data.emplace_back(IMAGE_ID("���")[1], 60);
	// ɰ�قɓo�^
	SetAnim(ANIM::NORMAL, data);

	// �̈��ύX
	data.reserve(1);
	data.emplace_back(IMAGE_ID("���")[2], 60);
	// EX�ɓo�^
	SetAnim(ANIM::EX, data);

	// �����p�ɗ̈��ύX
	data.reserve(5);
	for (int k = 0; k < 4; k++)
	{
		// �����p�摜�o�^
		data.emplace_back(IMAGE_ID("PL����")[k], 8 + (k * 8));

		if (k == 3)
		{
			data.emplace_back(-1, 8 + ((k + 1) * 8));
		}
	}
	// ������EX�Ɏw��
	SetAnim(ANIM::DEATH, data);

	// SE�̓o�^
	// �e
	lpSoundMng.SoundInit("sound/P_Bullet.mp3", "��ڲ԰��گ�");
	// ��Ұ��
	lpSoundMng.SoundInit("sound/Damage.mp3", "��Ұ��");
	// ���S
	lpSoundMng.SoundInit("sound/P_Destroy.mp3", "��ڲ԰���S");
	return true;
}

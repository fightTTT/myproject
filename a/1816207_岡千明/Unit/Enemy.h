#pragma once
#include "Obj.h"
#include "E_Bullet.h"

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(Vector2 pos);
	Enemy(Enemy_State state);
	~Enemy();

	void Draw(void)override;		// �`��֐�
	void UpDate(void)override;		// ��ԍX�V�p�֐�

	UNIT GetUnitType(void)override;	// ��݂�ID��Ԃ�

private:
	bool Init(void);				// �������p�֐�
	void SetAnimCnt(void);			// ��Ұ��ݶ��Ă̾��(�����𓝈ꂷ��)

	void (Enemy::*move)(void);		// �ړ������p�֐��߲��
	void Sigmoid(void);				// �ړ��p�֐�(���Ӳ��)
	void Spiral(void);				// �ړ��p�֐�(��])
	void MoveLR(void);

	ENEMY_TYPE _type;				// �G�̎�ޓo�^�p
	AIM_VEC _aim;					// �ړI�n
	int _moveCnt;					//_aim�̔z��p

	Vector2Dbl _startPos;			// �o���ʒu
	Vector2Dbl _len;				// �ړI�n�܂ł̋���

	bool _secSigFlag;				// 2��ڂ̼��Ӳ�ވړ��p�׸�

	float _radian;					// �p�x
	float _rad;						// ���a(�~�ړ��p)
	float _diameter;				// ���a(�~�ړ��p)

	bool _lrFlag;					// ���E�ړ��ڍs�׸�
	Vector2Dbl _centerPos;			// LR_MOVE�ړ��������Ɏg�p
	double _cnt;

	int _score;				// ����p
	int _gameCnt = 0;

	bool _shotFlag = false;
	std::shared_ptr<E_Bullet> _e_Bullet_ptr;		// �e�p�������߲���
	std::vector<shared_E_Blt> _e_Bullet_vec;		// �e�p�Œ蒷�z��
};


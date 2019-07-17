#pragma once
#include <tuple>
#include <vector>
#include "Obj.h"

enum class ENM_DATA
{
	POS,
	TYPE,
	SIZE,
	TARGTPOS,
	MAX
};

enum class ENM_TYPE
{
	A,
	B,
	C,
	MAX
};

enum class MOVE_TYPE
{
	SIGMOID,
	B,
	LR,
	MAX
};

using EnemyData = std::tuple<Vector2Dbl, ENM_TYPE, Vector2,Vector2Dbl>;
using MoveType = std::tuple<Vector2Dbl, MOVE_TYPE>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyData data);
	~Enemy();

	// override�Ə������Ƃɂ���ăI�[�o�[���C�h���Y��ɂ��o�O��h�~����
	void Draw(void) override;	
	UNIT GetUnit(void) override;
	void SetMove();
private:
	bool Init(void);
	void MoveSigmoid(void);
	void MoveB(void);
	void MoveLR(void);
	void (Enemy::*move)(void);	// �����o�֐��|�C���^
	ENM_TYPE _type;				// �G�̎��
	Vector2Dbl _targetPos;			// �G�����ԏꏊ
	Vector2Dbl _firstTarget;		// �G���ŏ��Ɍ������ꏊ
	int speed;
	bool firstFlag;
	int waitCnt;

	Vector2Dbl _posOld;
	static int animCnt;
	std::vector<MoveType> moveData;
	//-----------------
	float _floatPosX;
	float _floatPosY;
	//-----------------
};

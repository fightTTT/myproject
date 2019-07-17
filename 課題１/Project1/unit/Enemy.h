#pragma once
#include <tuple>
#include "Obj.h"

enum class ENM_DATA
{
	POS,
	TYPE,
	SIZE,
	TARGTPOS
};

enum class ENM_TYPE
{
	A,
	B,
	C
};

using EnemyData = std::tuple<Vector2Dbl, ENM_TYPE, Vector2,Vector2Dbl>;

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
	ENM_TYPE _type;				// �G�̎��
	Vector2Dbl _targetPos;			// �G�����ԏꏊ
	Vector2Dbl _firstTarget;		// �G���ŏ��Ɍ������ꏊ
	int speed;
	bool firstFlag;
	int waitCnt;
	Vector2Dbl _posOld;
	static int animCnt;
	//-----------------
	float _floatPosX;
	float _floatPosY;
	//-----------------
};

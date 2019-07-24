#pragma once
#include <tuple>
#include <vector>
#include<list>
#include <memory>
#include "Obj.h"

enum class ENM_DATA
{
	POS,
	TYPE,
	SIZE,
	TARGTPOS,
	ENEMNUM,
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
	SPIRAL,
	LR,
	MAX
};

using EnemyData = std::tuple<Vector2Dbl, ENM_TYPE, Vector2,Vector2Dbl,int>;
using MoveType = std::tuple<Vector2Dbl, MOVE_TYPE>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyData& data);
	~Enemy();

	// override�Ə������Ƃɂ���ăI�[�o�[���C�h���Y��ɂ��o�O��h�~����
	void Draw(void) override;	
	UNIT GetUnit(void) override;
	void SetMove();
private:
	bool Init(void);
	void MoveSigmoid(void);
	void MoveSpiral(void);
	void MoveLR(void);
	void MoveWait(void);
	void (Enemy::*move)(void);	// �����o�֐��|�C���^
	ENM_TYPE _type;				// �G�̎��
	Vector2Dbl _targetPos;			// �G�����ԏꏊ
	Vector2Dbl _firstTarget;		// �G���ŏ��Ɍ������ꏊ
	double speed;
	bool firstFlag;
	int waitCnt;
	int _enemCnt;

	Vector2Dbl _posOld;
	static int animCnt;
	std::vector<MoveType> moveData;
	Vector2Dbl _vel;
	//-----------------
	/*float _floatPosX;
	float _floatPosY;*/
	double X;
	double lastX;
	double Y;
	double lastY;
	Vector2Dbl debgPos;
	//-----------------
	std::list<Vector2Dbl> drawPixel;

	double step;
};

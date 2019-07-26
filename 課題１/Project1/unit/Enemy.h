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
	ENEMCNT,
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

using EnemyData = std::tuple<Vector2Dbl, ENM_TYPE, Vector2Dbl,Vector2Dbl,int,int>;
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

	// �V�O���C�h�Ȑ��œ���
	void MoveSigmoid(void);		
	// ��]
	void MoveSpiral(void);
	// �Ō�̖ڕW�n�_�Ɍ�����
	void MoveLastTraget(void);
	// ���E�ړ�
	void MoveLR(void);		
	// �G�̕ґ���wait�֐�
	void MoveWait(void);		

	void (Enemy::*move)(void);	// �����o�֐��|�C���^
	ENM_TYPE _type;				// ���
	Vector2Dbl _targetPos;		// ���ԏꏊ
	double speed;
	bool firstFlag;
	int waitCnt;
	int _enemCnt;

	Vector2Dbl _posOld;
	static int animCnt;
	static bool enemGather;
	int enemCounter;
	std::vector<MoveType> moveData;
	Vector2Dbl _vel;
	double step;


	//-----------------
	double X;
	Vector2Dbl debgPos;
	std::list<Vector2Dbl> drawPixel;
	//-----------------
};

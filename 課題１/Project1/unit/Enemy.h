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
	ENEMCNT,
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

using EnemyData = std::tuple<Vector2Dbl, ENM_TYPE, Vector2Dbl,Vector2Dbl,int,int>;

class EnemyMove;

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
	std::vector<Shared_Obj> GetShotData() override;

private:
	bool Init(void);
	void EnemDamage(void);		// �_���[�W���󂯂��Ƃ��̏����B�G�̐F��ς��A���C�t���[���ɂȂ�����E��

	ENM_TYPE _type;				// ���
	Vector2Dbl _targetPos;		// ���ԏꏊ

	
	int _enemCnt;

	Vector2Dbl _posOld;
	int enemNum;
	Vector2Dbl _vel;
	bool leftFlag; 
	int enemyAnimFrame;
	std::unique_ptr<EnemyMove> enemMoveData;

	//-----------------
	Vector2Dbl InstancePos;
	//-----------------
};

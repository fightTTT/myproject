#pragma once
#include "unit/Enemy.h"
#include "common/Vector2.h"

enum class MOVE_TYPE
{
	SIGMOID,
	SPIRAL,
	LR,
	MAX
};

using MoveType = std::tuple<Vector2Dbl, MOVE_TYPE>;		// ���ꂼ��̈ړ��̖ڕW�n�_		�ړ����@

class EnemyMove
{
public:
	EnemyMove();
	EnemyMove(EnemyData enemData);
	~EnemyMove();

	void Init(void);

	void SetMove(void);

	const Vector2Dbl GetPos(void) { return _pos; };
	const float GetAngle(void) { return _angle; };


private:
	static bool enemGather;

	// �G�̕ґ���wait�֐�
	void MoveWait(void);
	// �V�O���C�h�Ȑ��œ���
	void MoveSigmoid(void);
	// ��]
	void MoveSpiral(void);
	// �Ō�̖ڕW�n�_�Ɍ�����
	void MoveLastTarget(void);
	// ���E�ړ�
	void MoveLR(void);

	void MoveAttack(void);
	

	Vector2Dbl _pos;
	Vector2Dbl _posOld;
	Vector2Dbl _vel;
	Vector2Dbl _size;
	Vector2Dbl _targetPos;
	void (EnemyMove::*move)(void);	// �����o�֐��|�C���^
	float _angle;
	std::vector<MoveType> moveData;	 // �ړ����@�ƖڕW�n�_���i�[����vector
	bool leftFlag;					// �G����������o�������true�ɂ���
	int _enemNum;
	double speed;
	int _enemCnt;

	bool virtualMoveFlag;			// �U������true�ɂ���t���O
	Vector2Dbl virtualMovePos;		// �U�����̊g��k���̎����̍��W

	double X;
	double sigmoidStep;
	Vector2Dbl InstancePos;

};


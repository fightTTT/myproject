#pragma once
#include "unit/Enemy.h"

class EnemyMove
{
public:
	EnemyMove();
	EnemyMove(EnemyData enemData);
	~EnemyMove();

	// �V�O���C�h�Ȑ��œ���
	void MoveSigmoid(void);
	// ��]
	void MoveSpiral(void);
	// �Ō�̖ڕW�n�_�Ɍ�����
	void MoveLastTarget(void);
	// ���E�ړ�
	void MoveLR(void);
	// �G�̕ґ���wait�֐�
	void MoveWait(void);


};


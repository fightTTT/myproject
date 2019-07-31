bool EnemyDestroyed();
bool Catched();

// �����̏�ԁi�ߑ��C���V�C���́j
typedef enum {
	CAPTURED, FLOATING, DOCKED
} DOCKING_STATE;

// ���̂Ɋւ��鏈��
void Docking(
	float& cx, float& cy,  // �����̍��W
	float ex, float ey,    // �G�̍��W
	float mx, float my,    // ���@�̍��W
	DOCKING_STATE& state   // �����̏��
) {
	// �����̏�Ԃɂ���ĕ��򂷂�
	switch (state) {
		
		// �ߑ��F
		// �G�ƈꏏ�ɓ����B
		// �G���j�󂳂ꂽ�畂�V��ԂɈڍs����B
		// �G�̔j�󔻒菈����EnemyDestroyed�֐��ōs���Ƃ���B
		case CAPTURED:
			cx=ex; cy=ey;
			if (EnemyDestroyed()) state=FLOATING;
			break;
		
		// ���V�F
		// ���R�ɓ����B
		// �����ł͉�ʉ������ɒ��i����Ƃ���B
		// ���@�ɐڐG�����獇�̏�ԂɈڍs����B
		// �ڐG���菈����Catched�֐��ōs���Ƃ���B
		case FLOATING:
			cy++;
			if (Catched()) state=DOCKED;
			break;
		
		// ���́F
		// ���@�ƈꏏ�ɓ����B
		case DOCKED:
			cx=mx; cy=my;
			break;
	}
}


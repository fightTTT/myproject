bool CaptureAttack();
void NormalAttack();
bool Destroyed();
void ReturnMyShip();
void Delete();

// �G�̏�ԁF
// �ʏ�C�ߑ�
typedef enum {
	NORMAL, CAPTURED
} CAPTOR_STATE;

// ���@���Ƃ炦��G�̓���
void Captor(
	bool capture  // ����C�ߑ��U�������邩�ǂ���
) {
	static int state=NORMAL;  // �G�̏��
	
	// ��Ԃɂ���ĕ��򂷂�
	switch (state) {
		
		// �ʏ��ԁF
		// �ʏ�U���܂��͕ߑ��U�����s���B
		// �ߑ��U��������������ߑ���ԂɈڂ�B
		// �U���̋�̓I�ȏ����́CCaptureAttack�C
		// NormalAttack�̊e�֐��ōs���Ƃ���B
		case NORMAL:
			if (capture) {
				if (CaptureAttack()) state=CAPTURED;
			} else {
				NormalAttack();
			}
			break;
		
		// �ߑ���ԁF
		// �ʏ�U�����s���B
		// �j�󂳂ꂽ�玩�@��Ԃ�����ɏ��ł���B
		// ����Ȃǂ̋�̓I�ȏ����́CDestroyed�C
		// ReturnMyShip�CDelete�̊e�֐��ōs���Ƃ���B
		case CAPTURED:
			NormalAttack();
			if (Destroyed()) {
				ReturnMyShip();
				Delete();
			}
			break;
	}
}


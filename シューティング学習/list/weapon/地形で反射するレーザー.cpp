// ���[�U�[�̊e������\���\����
typedef struct LASER_STRUCT {
	float X, Y;                 // ������W
	float W, H;                 // ���ƍ���
	float VX, VY;               // ���x
	float OldX, OldY;           // �Â����W
	struct LASER_STRUCT* Prec;  // 1�O�̕���
	                            // �i�擪�����̏ꍇ�ɂ�NULL�j
} LASER_TYPE;

// ���[�U�[�𓮂����֐�
void MoveReflectLaser(
	LASER_TYPE* laser,         // ���[�U�[��1�̕���
	float gx0[], float gy0[],  // �n�`�̍�����W
	float gx1[], float gy1[],  // �n�`�̉E�����W
	int num_ground             // �n�`�̐�
) {
	// ��[�����̏ꍇ�F
	// �n�`�Ŕ��˂���V���b�g�̏����Ɠ����B
	if (!laser->Prec) {

		// �n�`�Ƃ̓����蔻�菈���F
		// ��[�����𐂒������ɐi�߂����W(X, Y+VY)�ɂ��āC
		// �n�`�ɓ����邩�ǂ����𔻒肷��B
		// �n�`�ɓ��������ꍇ�ɂ́C���������̑��x���t�ɂ��āC
		// ���[�v���甲����B
		for (int i=0; i<num_ground; i++) {
			if (gx0[i]<laser->X+laser->W &&
				laser->X<gx1[i] && 
				gy0[i]<laser->Y+laser->W+laser->VY &&
				laser->Y+laser->VY<gy1[i]
			) {
				laser->VX=-laser->VX;
				break;
			}
		}

		// ��[������i�߂�
		laser->X+=laser->VX;
		laser->Y+=laser->VY;
	}
	
	// ��[�����ȊO�̏ꍇ�F
	// 1�O�̕�����ǂ�������B
	// 1�O�̕����̌Â����W�ֈړ�����B
	else {
		laser->X=laser->Prec->OldX;
		laser->Y=laser->Prec->OldY;
	}
}


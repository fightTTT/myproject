void DamageEnemy(int id);

void MoveReflectShot(
	float& x0, float& y0,      // �V���b�g�̍�����W
	float& x1, float& y1,      // �V���b�g�̉E�����W
	float& vx, float& vy,      // �V���b�g�̑��x�i�����C�����j
	float gx0[], float gy0[],  // �n�`�̍�����W
	float gx1[], float gy1[],  // �n�`�̉E�����W
	int num_ground,            // �n�`�̐�
	float ex0[], float ey0[],  // �G�̍�����W
	float ex1[], float ey1[],  // �G�̉E�����W
	int num_enemy              // �G�̐�
) {
	// �n�`�Ƃ̓����蔻�菈���F
	// �V���b�g�𐂒������ɐi�߂����W�ɂ��āC
	// �n�`�ɓ����邩�ǂ����𔻒肷��B
	// �n�`�ɓ��������ꍇ�ɂ́C���������̑��x���t�ɂ��āC
	// ���[�v���甲����B
	for (int i=0; i<num_ground; i++) {
		if (gx0[i]<x1 && x0<gx1[i] && 
			gy0[i]<y1+vy && y0+vy<gy1[i]) {
			vy=-vy;
			break;
		}
	}
	
	// �V���b�g��i�߂�
	x0+=vx; y0+=vy;
	x1+=vx; y1+=vy;

	// �G�Ƃ̓����蔻�菈���F
	// �G�ɓ��������ꍇ�ɂ́C�G�Ƀ_���[�W��^���āC
	// ���[�v���甲����B
	// �_���[�W�̋�̓I�ȏ�����DamageEnemy�֐��ōs���Ƃ���B
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			break;
		}
	}
}


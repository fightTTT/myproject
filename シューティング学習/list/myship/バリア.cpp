void DeleteBullet(int id);
void DamageEnemy(int id);
void DeleteBarrier();

void Barrier1(
	float x0, float y0,        // �o���A�̓����蔻��
	float x1, float y1,        // �i������W�C�E�����W�j
	float bx0[], float by0[],  // �e�̓����蔻��
	float bx1[], float by1[],  // �i������W�C�E�����W�j
	int num_bullet,            // �e�̐�
	float ex0[], float ey0[],  // �G�̓����蔻��
	float ex1[], float ey1[],  // �i������W�C�E�����W�j
	int num_enemy,             // �G�̐�
	int& damage,               // �o���A�ɒ~�ς��ꂽ�_���[�W
	int max_damage             // �o���A�̃_���[�W�̌��E�l
) {
	// �o���A�ƒe�Ƃ̓����蔻�菈���F
	// �e������������C�e�������C�o���A�̃_���[�W�𑝂₷�B
	// �e��������̓I�ȏ�����DeleteBullet�֐��ōs���Ƃ���B
	for (int i=0; i<num_bullet && damage<max_damage; i++) {
		if (bx0[i]<x1 && x0<bx1[i] && 
			by0[i]<y1 && y0<by1[i]) {
			DeleteBullet(i);
			damage++;
		}
	}

	// �o���A�ƓG�Ƃ̓����蔻�菈���F
	// �G������������C�G�Ƀ_���[�W��^���C
	// �o���A�̃_���[�W�����₷�B
	// �G�Ƀ_���[�W��^�����̓I�ȏ����́C
	// DamageEnemy�֐��ōs���Ƃ���B
	for (int i=0; i<num_enemy && damage<max_damage; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DamageEnemy(i);
			damage++;
		}
	}
	
	// �_���[�W�����E�l�𒴂����Ƃ��F
	// �o���A�����ł�����B
	// ���ł̋�̓I�ȏ�����DeleteBarrier�֐��ōs���Ƃ���B
	if (damage>=max_damage) DeleteBarrier();
}

void Barrier2(
	float x0, float y0,        // �o���A�̓����蔻��
	float x1, float y1,        // �i������W�C�E�����W�j
	float bx0[], float by0[],  // �e�̓����蔻��
	float bx1[], float by1[],  // �i������W�C�E�����W�j
	int num_bullet,            // �e�̐�
	float ex0[], float ey0[],  // �G�̓����蔻��
	float ex1[], float ey1[],  // �i������W�C�E�����W�j
	int num_enemy,             // �G�̐�
	int& energy,               // �o���A�̃G�l���M�[
	bool barrier_button        // �o���A�{�^���̏��
) {
	// �o���A�𒣂�F
	// �o���A�{�^����������Ă���C
	// ���G�l���M�[������Ƃ��ɂ́C�o���A�𒣂�B
	if (barrier_button && energy>0) {
	
		// �o���A�ƒe�Ƃ̓����蔻�菈���F
		// �e������������C�e�������C�o���A�̃G�l���M�[�����炷�B
		// �e��������̓I�ȏ�����DeleteBullet�֐��ōs���Ƃ���B
		for (int i=0; i<num_bullet && energy>0; i++) {
			if (bx0[i]<x1 && x0<bx1[i] && 
				by0[i]<y1 && y0<by1[i]) {
				DeleteBullet(i);
				energy--;
			}
		}

		// �o���A�ƓG�Ƃ̓����蔻�菈���F
		// �G������������C�G�Ƀ_���[�W��^���C
		// �o���A�̃G�l���M�[�����炷�B
		// �G�Ƀ_���[�W��^�����̓I�ȏ����́C
		// DamageEnemy�֐��ōs���Ƃ���B
		for (int i=0; i<num_enemy && energy>0; i++) {
			if (ex0[i]<x1 && x0<ex1[i] && 
				ey0[i]<y1 && y0<ey1[i]) {
				DamageEnemy(i);
				energy--;
			}
		}

		// �G�l���M�[�̏���
		energy--;
	}
}



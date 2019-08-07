void DeleteMyLaser(int id);
void DeleteEnemyLaser(int id);
void SpecialAttack();

void LaserCollision(
	float mx0[], float my0[],  // ���@���[�U�[�̈ꕔ�̍�����W
	float mx1[], float my1[],  // ���@���[�U�[�̈ꕔ�̉E�����W
	int num_my_lasers,         // ���@���[�U�[�̕����̐�
	float ex0[], float ey0[],  // �G���[�U�[�̈ꕔ�̍�����W
	float ex1[], float ey1[],  // �G���[�U�[�̈ꕔ�̉E�����W
	int num_enemy_lasers       // �G���[�U�[�̕����̐�
) {
	static int energy=0;        // �G�l���M�[
	static int min_energy=100;  // �U���̔����ɕK�v�ȃG�l���M�[
	
	// ���[�U�[���m�̓����蔻�菈���F
	// ���@���[�U�[�ƓG���[�U�[�̊e�������m���Ԃ�������C
	// 2�̕��������ł����ăG�l���M�[�𑝂₷�B
	// ���ł̋�̓I�ȏ����́CDeleteMyLaser�C
	// DeleteEnemyLaser�̊e�֐��ōs���Ƃ���B
	for (int i=0; i<num_my_lasers; i++) {
		for (int j=0; j<num_enemy_lasers; j++) {
			if (ex0[j]<mx1[i] && mx0[i]<ex1[j] && 
				ey0[j]<my1[i] && my0[i]<ey1[j]) {
				DeleteMyLaser(i);
				DeleteEnemyLaser(j);
				energy++;
			}
		}
	}
	
	// �U���̔����F
	// �G�l���M�[���K�v�ʂɒB���Ă�����C
	// ���͂ȍU���𔭐�������B
	// �����̋�̓I�ȏ�����SpecialAttack�֐��ōs���Ƃ���B
	if (energy>=min_energy) SpecialAttack();
}


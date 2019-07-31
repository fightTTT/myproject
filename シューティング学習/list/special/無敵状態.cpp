void DamageEnemy(int id);
void DeleteBullet(int id);
void Miss();

void Invincible(
	bool invincible,           // ���G��ԂȂ��true
	float x0, float y0,        // ���@�̍�����W
	float x1, float y1,        // ���@�̉E�����W
	float ex0[], float ey0[],  // �G�̍�����W
	float ex1[], float ey1[],  // �G�̍�����W
	int num_enemy,             // �G�̐�
	float bx0[], float by0[],  // �e�̍�����W
	float bx1[], float by1[],  // �e�̍�����W
	int num_bullet             // �e�̐�
) {
	// �G�Ƃ̓����蔻�菈���F
	// �G�ƂԂ������ꍇ�C���G��ԂȂ�ΓG�Ƀ_���[�W��^���C
	// �ʏ��ԂȂ�΃~�X�Ƃ���B
	// �_���[�W�t�^�ƃ~�X�̋�̓I�ȏ����́C
	// DamageEnemy�CMiss�̊e�֐��ōs���Ƃ���B
	for (int i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			if (invincible) DamageEnemy(i); else Miss();
		}
	}
	
	// �e�Ƃ̓����蔻�菈���F
	// �e�ƂԂ������ꍇ�C���G��ԂȂ�Βe�������C
	// �ʏ��ԂȂ�΃~�X�Ƃ���B
	// �����ƃ~�X�̋�̓I�ȏ����́C
	// DeleteBullet�CMiss�̊e�֐��ōs���Ƃ���B
	for (int i=0; i<num_bullet; i++) {
		if (bx0[i]<x1 && x0<bx1[i] && 
			by0[i]<y1 && y0<by1[i]) {
			if (invincible) DeleteBullet(i); else Miss();
		}
	}
}
